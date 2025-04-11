#!/bin/sh

DISK="$1"
#DISK=/dev/sdb

if [ -z "${DISK}" ]; then
	echo "Please input the block devcie name"
	echo "Usage: ./part_disk.sh /dev/sdb"

	exit 0
fi


parted ${DISK} --script mklabel msdos
parted -a optimal ${DISK} --script mkpart primary fat32 8192s 142958s
parted -a optimal ${DISK} --script mkpart primary ext4 142959s 392959s
mkfs.vfat -n BOOT -F 32 ${DISK}1
yes| mkfs.ext4 -L MEME5019 ${DISK}2

mkdir -p /mnt/p1 /mnt/p2
mount ${DISK}1 /mnt/p1
mount ${DISK}2 /mnt/p2

cp -a ./boot/* /mnt/p1
tar -xJvf rootfs.tar.xz
cp -a ./rootfs/* /mnt/p2

umount /mnt/p1
umount /mnt/p2
