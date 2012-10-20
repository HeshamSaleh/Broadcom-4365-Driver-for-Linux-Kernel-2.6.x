Broadcom-4365-Driver-for-Linux-Kernel-2.6.x
===========================================
This is a personal repository for a debian version from twelveeighty's patch (from ArchLinux's forum) to allow the Broadcom 4365 driver to work on Linux Kernel 3.6.x

Original Forum Topic: https://bbs.archlinux.org/viewtopic.php?id=145884&p=2

Original ArchLinux Package on Aur: http://aur.archlinux.org/packages.php?ID=62666

How to use ?
------------

From Binary:

- Simply download the debian package from the bin directory on this repo, and install it

`wget https://github.com/HeshamSaleh/Broadcom-4365-Driver-for-Linux-Kernel-2.6.x/blob/master/bin/wireless-bcm43142-dkms-6.20.55.19_amd64.deb`

`dpkg --install wireless-bcm43142-dkms-6.20.55.19_amd64.deb`

From Source:

- Patch the driver with the supplied patch

`cd usr/src/wireless-bcm43142-oneiric-dkms-6.20.55.19~bdcom0602.0400.1000.0400`

`patch -p1 < patches/0001-Makefile.patch`

- `make` it, or even better, `dpkg --build wireless-bcm43142-dkms-6.20.55.19_amd64`

- Install it (if you used `dpkg --build`, then `dpkg --install` it)

- To test without restarting, add the wl module to your kernel by `modprobe wl`

- Test if your WLAN card is working through `iwconfig`

------------
Tested on Linux Mint 13 (Maya) Mate on a Dell Inspiron 5520
