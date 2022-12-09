qemu-system-aarch64 \
  -m 4G \
  -cpu cortex-a57 \
  -M virt \
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
  -netdev user,id=mynet,net=192.168.76.0/24,dhcpstart=192.168.76.9 \
  -device virtio-net-pci,netdev=mynet \
  -netdev user,id=mynet2,hostfwd=::5555-:22 \
  -device virtio-net-pci,netdev=mynet2 \
  -append "rw earlyprintk modules=ext4,virtio_blk quiet loglevel=8 console=ttyAMA0,115200 root=/dev/vda3 rootwait=1"

# set KEGERATOR_SONG_LIST