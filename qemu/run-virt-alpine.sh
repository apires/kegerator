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

if [[ ! -d "./virt-alpine" ]]; then
    mkdir ./virt-alpine
    curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/alpine-standard-3.17.0-aarch64.iso -o virt-alpine/alpine-standard-3.17.0-aarch64.iso
    7z e ~/Downloads/alpine-standard-3.17.0-aarch64.iso -o./virt-alpine boot/vmlinuz-lts boot/initramfs-lts
    qemu-img create ./virt-alpine/disk.img 8G
fi


qemu-system-aarch64 \
  -m $SIZE \
  -cpu cortex-a53 \
  -M virt \
   -kernel ./virt-alpine/vmlinuz-lts \
  -initrd ./virt-alpine/initramfs-lts \
  -nographic \
  -drive if=none,file=./virt-alpine/disk.img,id=hd0,format=raw \
  -device virtio-blk-device,drive=hd0 \
  -drive if=none,file=virt-alpine/alpine-standard-3.17.0-aarch64.iso,id=hd1,format=raw \
  -device virtio-blk-device,drive=hd1 \
  -netdev user,id=mynet,hostfwd=::5555-:22 \
  -device virtio-net-pci,netdev=mynet \
  -append "rw earlyprintk modules=af_packet,ext4 quiet loglevel=8 console=ttyAMA0,115200 rootwait=1"
  

#   -append "rw earlyprintk loglevel=8 console=ttyAMA0,115200 ip=dhcp:::::eth0 ssh_key=\"$SSH_KEY\"" #alpine doesn't dhcp us :/
