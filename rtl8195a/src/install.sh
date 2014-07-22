#!/bin/bash
rmmod inic_8195a
rm /dev/inic_8195a
insmod /home/sd1/Projects/rtl8195a/Ameba_sdio_device/rtl8195a/src/inic_8195a.ko
mknod /dev/inic_8195a c 249 0