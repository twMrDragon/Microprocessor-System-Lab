obj-m := hellod.o

kernel_DIR := /usr/src/linux-headers-4.9.201-tegra-ubuntu18.04_aarch64/kernel-4.9

PWD := $(shell pwd)

all:
	make -C $(kernel_DIR) SUBDIRS=$(PWD)

clear:
	rm *.o *.ko *.mod.c

.PHONY:
	clean