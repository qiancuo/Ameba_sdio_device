EXTRA_CFLAGS = -I$(shell pwd)/include
#ifneq ($(KERNELRELEASE),)
	obj-m := inic_8195a.o
	inic_8195a-objs := rtl8195a.o hal/rtl8195a/sdio/sdio_ops.o osdep/linux/osdep_service_linux.o \
						core/rtw_debug.o
#else
#	BASEDIR := /lib/modules/$(shell uname -r)
#	KERNELDIR ?= $(BASEDIR)/build
	PWD :=$(shell pwd)
#	DRIVERDIR := $(shell find $(BASEDIR)/kernel/drivers/net -name realtek -type d)
#	ifeq ($(DRIVERDIR),)
#		DRIVERDIR := $(BASEDIR)/kernel/drivers/net
#		endif
#	RTKDIR := $(subst $(BASEDIR)/,,$(DRIVERDIR))
	KERNEL_DIR := /lib/modules/$(shell uname -r)/build
.PHONY: all
all: clean modules

.PHONY:modules
modules:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) $(EXTRA_CFLAGS) modules

.PHONY:clean
clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

#.PHONY:install
#install:
#	$(MAKE) -C $(KERNELDIR) SUBDIRS=$(PWD) INSTALL_MOD_DIR=$(RTKDIR) modules_install

#endif

