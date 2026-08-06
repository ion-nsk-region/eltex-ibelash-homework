obj-m +=module_pr_info.o
obj-m +=module_dev.o
obj-m +=module_proc_fs.o

# Добавляем заголовочные файлы из текущей директории
ccflags-y += -I$(PWD)

SRCS := $(filter-out %.mod.c, $(wildcard *.c))

all: code_check build_modules

code_check: $(SRCS)
	clang-format -i --style=Google $^
	-cppcheck --enable=all --suppress=missingIncludeSystem $^

build_modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) C=2 modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	find -name "*~" -delete

.PHONY: all code_check build_system clean
