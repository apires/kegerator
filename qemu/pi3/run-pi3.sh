#!/bin/bash

SIZE=4G

if [[ ! -d "./image" ]]; then
    mkdir ./image
fi

if [[ ! -f "./image/root.qcow2" ]]; then
    echo "Root image not found, making it"
    curl https://downloads.raspberrypi.org/raspios_lite_arm64/images/raspios_lite_arm64-2022-09-26/2022-09-22-raspios-bullseye-arm64-lite.img.xz -o 2022-09-22-raspios-bullseye-arm64-lite.img.xz
    echo "Decompressing it"
    7z e 2022-09-22-raspios-bullseye-arm64-lite.img.xz 
    7z e 2022-09-22-raspios-bullseye-arm64-lite.img 0.fat
    7z e 0.fat -o./image kernel8.img bcm2710-rpi-3-b.dtb
    qemu-img resize ./2022-09-22-raspios-bullseye-arm64-lite.img $SIZE
    echo 'pi:$6$ti16Gf18l8nFRiUD$bD5JVzE7p7MC57S7Xp5tuMFZnSlnqy7hzgbrZ2mRWOrKRhB1nIWAXWjobqHIMcfxjRT4Wsz.czbC3l.mxyw3Q/' > userconf.txt
    touch ssh
    mcopy -i 0.fat userconf.txt ::
    mcopy -i 0.fat ssh ::
    dd if=0.fat of=2022-09-22-raspios-bullseye-arm64-lite.img seek=8192 conv=notrunc
    qemu-img convert 2022-09-22-raspios-bullseye-arm64-lite.img -O qcow2 image/root.qcow2
    rm 0.fat 
    rm 2022-09-22-raspios-bullseye-arm64-lite.img
    rm userconf.txt
    rm 2022-09-22-raspios-bullseye-arm64-lite.img.xz
    rm ssh
fi

qemu-system-aarch64 \
    -machine raspi3b -smp 4\
    -dtb image/bcm2710-rpi-3-b.dtb \
    -kernel image/kernel8.img \
    -drive format=qcow2,file=image/root.qcow2 \
    -usb \
    -device usb-kbd \
    -device usb-mouse \
    -nographic \
    -device usb-net,netdev=net0 \
	-netdev user,id=net0,hostfwd=tcp::6666-:22 \
    -append "rw earlyprintk loglevel=8 console=ttyAMA0,115200 root=/dev/mmcblk0p2 rootdelay=1"
