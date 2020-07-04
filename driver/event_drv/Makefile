obj-m :=event_drv.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:clean
	- make -C $(KERNEL_DIR) M=$(PWD) modules

insmod:all
	- $(shell insmod event_drv.ko)

clean:
	rm *.o *.ko *.mod.c
