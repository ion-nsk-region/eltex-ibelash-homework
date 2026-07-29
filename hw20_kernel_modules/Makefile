obj-m +=module_pr_info.o
obj-m +=module_dev.o
obj-m +=module_proc_fs.o

# Добавляем заголовочные файлы из текущей директории
ccflags-y += -I$(PWD)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

