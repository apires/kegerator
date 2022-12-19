#!/usr/bin/expect -f

set timeout -1

if { ! [ file exists build_artifacts ] } {
    system mkdir build_artifacts
    system curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/initramfs-rpi -o build_artifacts/initramfs-rpi
    system curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/vmlinuz-rpi -o build_artifacts/vmlinuz-rpi
    system curl https://raw.githubusercontent.com/raspberrypi/firmware/master/boot/bcm2710-rpi-3-b.dtb -o build_artifacts/bcm2710-rpi-3-b.dtb
    #if we can serve this locally we don't need to download it twice
    system curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/modloop-rpi -o build_artifacts/modloop-rpi 
} else {
    puts {Reusing build artifacts}
}

if {[ file exists hda.qcow2 ]} {
    puts {Removing incomplete .img file...}
    system rm hda.qcow2
}

system qemu-img create -f qcow2 hda.qcow2 4g

set SSH_KEY [exec ssh-add -L | grep Development]

# un7zip modloop and concat to initrd so we can get the qemu network driver


# Doesn't work with alpine because alpine doesn't bundle soft ethernet drivers and qemu doesn't implement LAN7515
spawn qemu-system-aarch64 \
    -M raspi3b --accel tcg,thread=multi -smp 4 \
    -dtb build_artifacts/bcm2710-rpi-3-b.dtb \
    -kernel build_artifacts/vmlinuz-rpi \
    -initrd build_artifacts/bleh/initap.gz \
    -drive format=qcow2,file=hda.qcow2 \
    -usb \
    -device usb-kbd \
    -device usb-tablet \
    -nographic \
    -device usb-net,netdev=net0 \
    -netdev user,id=net0,hostfwd=tcp::6666-:22 \
    -append "ip=dhcp alpine_repo=http://dl-cdn.alpinelinux.org/alpine/latest-stable/main/ console=ttyAMA0,115200 ssh_key=\"$SSH_KEY\""


expect -exact "localhost login: "
send "root\r"
expect {localhost:~# }
send "export TERM=dumb\r"
send "TERM=dumb setup-alpine\r"
expect -re {Enter system hostname.*] }
send "qemu-pi3\r"
expect -re {Which one do you want to initialize.*] }
send -- "eth0\r"
expect -re {Ip address for eth0.*] }
send -- "dhcp\r"
expect -re {Do you want to do any manual network configuration.*] }
send -- "n\r"
expect "New password:"
send -- "n\r"
expect "Retype password:"
send -- "n\r"
expect -re {Which timezone are you in.*] }
send -- "UTC\r"
expect -re {HTTP/FTP proxy.*] }
send -- "\r"
expect -re {Which NTP client to run.*] }
send -- "\r"
send -- "q"
expect -re {Enter mirror number.*] }
send -- "1\r"
expect -re {Setup a user.*] }
send -- "no\r"
expect -re {Which ssh server.*] }
send -- "openssh\r"
expect -re {Allow root ssh login.*] }
send "yes\r"
expect -re {Enter ssh key or URL for root.*] }
send "none\r"
expect -re {Which disk.*] }
send "mmcblk0\r"
expect -re {How would you like to use it.*] }
send "sys\r"
expect {WARNING: Erase the above disk}
send -- "y\r"

expect "mkfs.fat"
expect "Installing system on /dev/mmcblk0p2"

expect {Installation is complete}

# send "mount -t ext4 /dev/vda3 /mnt\r"
# send "chroot /mnt\r"
# expect "/ # "
# send "export TERM=dumb\r"
# expect "/ # "

# send "echo 'http://dl-cdn.alpinelinux.org/alpine/latest-stable/main/' > /etc/apk/repositories\r"
# expect "/ # "
# send "echo 'http://dl-cdn.alpinelinux.org/alpine/v3.17/main/' >> /etc/apk/repositories\r"
# expect "/ # "
# send "echo 'http://dl-cdn.alpinelinux.org/alpine/v3.17/community/' >> /etc/apk/repositories\r"
# expect "/ # "
# send "apk update\r"
# expect -re {OK.*packages}

# send "apk add terminus-font ttf-inconsolata ttf-dejavu ttf-font-awesome qemu-virtiofsd\r"
# expect -re {OK.*packages}
# expect "/ # "
# send "apk add qt6-qtmultimedia libgpiod glog  gst-plugins-ugly gst-plugins-good gst-plugins-bad\r"
# expect -re {OK.*packages}
# expect "/ # "

# send "setup-devd\r"
# expect -re {What program should manage.*] }
# send "udev\r"
# expect -re {Scan the hardware to populate.*] } 
# send "y\r"
# expect "/ # "

# send "passwd -d root\r"
# expect "passwd: password for root changed by root"

# send "echo '//10.0.2.4/qemu /kegerator.qt   cifs    user=,pass=,vers=3.1  0 0' >> /etc/fstab\r"
# expect "/ # "

send "exit\r"
send "halt\r"

# system mkdir image
# system 7z e hda.qcow2 0.img
# system 7z e 0.img vmlinuz-rpi initramfs-rpi
# system rm 0.img
# system mv hda.qcow2 vmlinuz-rpi initramfs-rpi image
# system rm -rf build_artifacts