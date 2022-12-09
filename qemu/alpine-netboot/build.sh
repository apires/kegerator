#!/usr/bin/expect -f

set timeout -1

if {![ file exists build_artifacts]} {
    system mkdir build_artifacts
    system curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/initramfs-lts -o build_artifacts/initramfs-lts
    system curl https://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/vmlinuz-lts -o build_artifacts/vmlinuz-lts
} else {
    puts {Reusing build artifacts}
}

if {[ file exists hda.img ]} {
    puts {Removing incomplete .img file...}
    system rm hda.img
} else {
    system qemu-img create -f qcow2 hda.img 4g
}

set SSH_KEY [exec ssh-add -l | grep Development]
spawn qemu-system-aarch64 \
 -m 4G \
 -cpu cortex-a57 \
 -M virt \
 -kernel build_artifacts/vmlinuz-lts \
 -initrd build_artifacts/initramfs-lts \
 -nographic \
 -hda hda.img \
  -netdev user,id=mynet,net=192.168.76.0/24,dhcpstart=192.168.76.9 \
  -device virtio-net-pci,netdev=mynet \
  -netdev user,id=mynet2,hostfwd=::5555-:22 \
  -device virtio-net-pci,netdev=mynet2 \
 -append "console=ttyAMA0,115200 ssh_key=\"$SSH_KEY\" ip=dhcp alpine_repo=http://dl-cdn.alpinelinux.org/alpine/latest-stable/main/ modloop=http://dl-cdn.alpinelinux.org/alpine/v3.17/releases/aarch64/netboot/modloop-lts"

expect -exact "localhost login: "
send "root\r"
expect {localhost:~# }
send "export TERM=dumb\r"
send "TERM=dumb setup-alpine\r"
expect -re {Enter system hostname.*] }
send "qemu-alpine\r"
expect -re {Which one do you want to initialize.*] }
send -- "eth0\r"
expect -re {Ip address for eth0.*] }
send -- "dhcp\r"
expect -re {Which one do you want to initialize.*] }
send -- "eth1\r"
expect -re {Ip address for eth1.*] }
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
send "vda\r"
expect -re {How would you like to use it.*] }
send "sys\r"
expect -re {WARNING: Erase the above disk.*] }
send "y\r"
expect {Installation is complete. Please reboot.}

send "mount -t ext4 /dev/vda3 /mnt\r"
send "chroot /mnt\r"
expect "/ # "
send "export TERM=dumb\r"
expect "/ # "

send "echo 'http://dl-cdn.alpinelinux.org/alpine/latest-stable/main/' > /etc/apk/repositories\r"
expect "/ # "
send "echo 'http://dl-cdn.alpinelinux.org/alpine/v3.17/main/' >> /etc/apk/repositories\r"
expect "/ # "
send "echo 'http://dl-cdn.alpinelinux.org/alpine/v3.17/community/' >> /etc/apk/repositories\r"
expect "/ # "
send "apk update\r"
expect -re {OK.*packages}

send "apk add terminus-font ttf-inconsolata ttf-dejavu ttf-font-awesome\r"
expect -re {OK.*packages}
expect "/ # "
send "apk add qt6-qtmultimedia libgpiod glog  gst-plugins-ugly gst-plugins-good gst-plugins-bad\r"
expect -re {OK.*packages}
expect "/ # "

send "setup-devd\r"
expect -re {What program should manage.*] }
send "udev\r"
expect -re {Scan the hardware to populate.*] } 
send "y\r"
expect "/ # "

send "exit\r"
send "halt\r"

system mkdir image
system 7z e hda.img 0.img
system 7z e 0.img vmlinuz-lts initramfs-lts
system rm 0.img
system mv hda.img vmlinuz-lts initramfs-lts image
system rm -rf build_artifacts