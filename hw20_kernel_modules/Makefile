obj-m +=module_pr_info.o

all:
	make -C /lib/modules/7.0.0-dirty/build M=$(PWD) modules

clean:
	make -C /lib/modules/7.0.0-dirty/build M=$(PWD) clean

