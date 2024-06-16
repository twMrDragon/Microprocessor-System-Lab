obj-m := demo.o

kernel_DIR := /usr/src/linux-headers-$(shell uname -r)

PWD := $(shell pwd)

all:
	make -C $(kernel_DIR) M=$(PWD)

clear:
	rm *.o *.ko *.mod.c

.PHONY:
	clean