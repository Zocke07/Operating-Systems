obj-m += jiffies_module.o seconds_module.o

KERNEL_DIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean

install:
	sudo insmod jiffies_module.ko
	sudo insmod seconds_module.ko

uninstall:
	sudo rmmod jiffies_module
	sudo rmmod seconds_module
