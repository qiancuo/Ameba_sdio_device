#EXTRA_CFLAGS += $(USER_EXTRA_CFLAGS)
#EXTRA_CFLAGS += -O1
#EXTRA_CFLAGS += -O3
#EXTRA_CFLAGS += -Wall
#EXTRA_CFLAGS += -Wextra
#EXTRA_CFLAGS += -Werror
#EXTRA_CFLAGS += -pedantic
#EXTRA_CFLAGS += -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

#EXTRA_CFLAGS += -Wno-unused-variable
#EXTRA_CFLAGS += -Wno-unused-value
#EXTRA_CFLAGS += -Wno-unused-label
#EXTRA_CFLAGS += -Wno-unused-parameter
#EXTRA_CFLAGS += -Wno-unused-function
#EXTRA_CFLAGS += -Wno-unused

PWD :=$(shell pwd)
EXTRA_CFLAGS += -I$(PWD)/include/
#CFLAGS += $(EXTRA_CFLAGS)
KERNEL_DIR := /lib/modules/$(shell uname -r)/build

CC = gcc
#ifneq ($(KERNELRELEASE),)
obj-m := inic_8195a.o
inic_8195a-objs := rtl8195a.o hal/rtl8195a/sdio/sdio_ops.o osdep/linux/osdep_service_linux.o \
					core/rtw_debug.o
#else
#	BASEDIR := /lib/modules/$(shell uname -r)
#	KERNELDIR ?= $(BASEDIR)/build

#	DRIVERDIR := $(shell find $(BASEDIR)/kernel/drivers/net -name realtek -type d)
#	ifeq ($(DRIVERDIR),)
#		DRIVERDIR := $(BASEDIR)/kernel/drivers/net
#		endif
#	RTKDIR := $(subst $(BASEDIR)/,,$(DRIVERDIR))

.PHONY: all
all: clean modules

.PHONY:modules
modules:
	$(MAKE) $(EXTRA_CFLAGS) -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules

.PHONY:clean
clean:
	$(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD) clean

#.PHONY:install
#install:
#	$(MAKE) -C $(KERNELDIR) SUBDIRS=$(PWD) INSTALL_MOD_DIR=$(RTKDIR) modules_install

#endif

