obj-m += hello_module.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all clean format check

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

format:
	clang-format -i hello_module.c

check:
	sudo insmod hello_module.ko || true
	sleep 1	
	sudo rmmod hello_module
