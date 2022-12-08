#!/bin/bash

SIZE=4G

if [[ ! -d "./pi3" ]]; then
    mkdir ./pi3
fi

# if [[ ! -f "./pi3/bcm2710-rpi-3-b.dtb" ]]; then 
#     echo "Device tree not found, downloading it."
#     curl https://raw.githubusercontent.com/raspberrypi/firmware/stable/boot/bcm2710-rpi-3-b.dtb -o pi3/bcm2710-rpi-3-b.dtb
# fi

# if [[ ! -f "./pi3/kernel8.img" ]]; then
#     echo "Kernel not found, downloading it (qemu boots from the kernel directly)"
#     curl https://raw.githubusercontent.com/raspberrypi/firmware/stable/boot/kernel8.img -o ./pi3/kernel8.img
# fi

if [[ ! -d "./pi3" ]]; then
    echo "Root image not found, downloading it"
    curl https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-2022-09-07/2022-09-06-raspios-bullseye-arm64-lite.img.xz -o ./pi3/2022-09-06-raspios-bullseye-arm64-lite.img.xz
    echo "Decompressing it"
    7z e ./pi3/2022-09-06-raspios-bullseye-arm64-lite.img.xz -o./pi3
    7z e ./pi3/2022-09-06-raspios-bullseye-arm64-lite.img -o./pi3 0.fat
    7z e ./pi3/0.fat -o./pi3 kernel8.img bcm2710-rpi-3-b.dtb
    qemu-img resize ./pi3/2022-09-06-raspios-bullseye-arm64-lite.img $SIZE
    rm ./pi3/0.fat rm ./pi3/2022-09-06-raspios-bullseye-arm64-lite.img.xz
fi

qemu-system-aarch64 \
    -machine raspi3b \
    -dtb ./pi3/bcm2710-rpi-3-b.dtb \
    -kernel ./pi3/kernel8.img \
    -drive format=raw,file=./pi3/2022-09-06-raspios-bullseye-arm64-lite.img \
    -usb \
	-device usb-net,netdev=net0 \
	-netdev user,id=net0,hostfwd=tcp::5555-:22 \
    -nographic \
    -append "rw earlyprintk loglevel=8 console=ttyAMA0,115200 root=/dev/mmcblk0p2 rootdelay=1 single init=/bin/bash"
