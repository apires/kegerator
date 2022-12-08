qemu-system-aarch64 \
  -m 4G \
  -cpu cortex-a53 \
  -M virt \
  -kernel artifacts/vmlinuz-lts \
  -initrd artifacts/initramfs-lts \
  -device virtio-gpu-pci \
  -hda hda.img \
  -device nec-usb-xhci \
  -usb \
  -device usb-mouse \
  -device usb-kbd \
  -device usb-audio \
  -netdev user,id=mynet,net=192.168.76.0/24,dhcpstart=192.168.76.9 \
  -device virtio-net-pci,netdev=mynet \
  -netdev user,id=mynet2,hostfwd=::5555-:22 \
  -device virtio-net-pci,netdev=mynet2 \
  -append "rw earlyprintk modules=virtio_gpu,af_packet,ext4,virtio_blk quiet loglevel=8 console=ttyAMA0,115200 root=/dev/vda3 rootwait=1"

# configure udev

# install:
# qt6-qtmultimedia
# libgpiod
# glog
# fonts
# gst-plugins-ugly gst-plugins-good gst-plugins-bad
# set KEGERATOR_SONG_LIST