PWD :=$(shell pwd)
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

obj-m := inic_8195a.o
inic_8195a-objs := rtl8195a.o osdep/linux/sdio_ops_linux.o  hal/rtl8195a/sdio/sdio_ops.o core/rtw_debug.o \
				osdep/osdep_service.o osdep/linux/osdep_service_linux.o osdep/linux/os_intfs.o \
				osdep/linux/rtw_proc.o osdep/linux/ioctl_linux.o osdep/linux/xmit_linux.o \
				core/rtw_xmit.o core/rtw_io.o

.PHONY: all
all: clean modules

.PHONY:modules
modules:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

.PHONY:clean
clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean


