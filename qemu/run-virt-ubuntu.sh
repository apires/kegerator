#!/bin/bash

SIZE=4G
SSH_KEY=$(ssh-add -L | grep Development)

if [[ -z "SSH_AUTH_SOCK" ]]; then
    echo "You need an ssh agent thingy."
    exit -1
fi

# if [[ ! -f "7z" ]]; then
#     echo "You need the 7z CLI tools"
#     exit -1
# fi

if [[ ! -d "./virt-ubuntu" ]]; then
    mkdir ./virt-ubuntu
    # cp ~/Downloads/lunar-server-cloudimg-arm64.img ./virt-ubuntu/lunar-server-cloudimg-arm64.img 
    curl http://cloud-images.ubuntu.com/lunar/current/lunar-server-cloudimg-arm64.img -o virt-ubuntu/lunar-server-cloudimg-arm64.img
    # 7z e ./virt-ubuntu/lunar-server-cloudimg-arm64.img 1.img
    # 7z e 1.img 
    # 7z e 0.img boot/vmlinuz boot/initrd.img -o./virt-ubuntu
    # rm 0.img
fi

qemu-system-aarch64 \
  -m $SIZE \
  -cpu cortex-a57 \
  -M virt \
  -nographic \
  -pflash ./efi/QEMU_EFI.fd \
  -pflash ./virt-ubuntu/flash1.img \
  -drive if=none,file=./virt-ubuntu/lunar-server-cloudimg-arm64.img,id=hd0,format=raw \
  -device virtio-blk-device,drive=hd0 \
  -netdev user,id=mynet,hostfwd=::5555-:22 \
  -device virtio-net-pci,netdev=mynet
