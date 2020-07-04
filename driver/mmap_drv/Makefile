obj-m :=mmp_drv.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
EXEC := test

all:$(EXEC)
	- make -C $(KERNEL_DIR) M=$(PWD) modules

insmod:all
	- $(shell insmod mmp_drv.ko)

clean:
	rm *.o *.ko *.mod.c test a.out

$(EXEC):mmp_test.c
	gcc $< -o $@