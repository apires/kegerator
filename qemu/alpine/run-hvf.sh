qemu-system-aarch64 \
  -M virt,accel=hvf \
  -m 4G \
  -cpu host \
  -kernel image/vmlinuz-lts \
  -initrd image/initramfs-lts \
  -device virtio-gpu-pci \
  -hda image/hda.img \
  -device nec-usb-xhci \
  -serial stdio \
  -usb \
  -device usb-mouse \
  -device usb-kbd \
  -device usb-audio \
  -netdev user,id=mynet2,hostfwd=::5555-:22,smb=$(realpath ../../) \
  -device virtio-net-pci,netdev=mynet2 \
  -append "rw earlyprintk modules=virtio_gpu,ext4,virtio_blk loglevel=8 console=ttyAMA0,115200 root=/dev/vda3 rootwait=1"

#mount -vvvv -t cifs //10.0.2.4/qemu /kegerator.qt/ -o username=root