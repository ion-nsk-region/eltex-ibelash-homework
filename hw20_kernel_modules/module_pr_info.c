// Добавляем имя модуля ко всем сообщениям https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_fmt
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, выводящий сообщения о своей загрузке и выгрузке.");
MODULE_VERSION("1.0");

int init_module(void) {
    pr_info("Модуль загружен\n");

    return 0;
}

void cleanup_module(void) {
    pr_info("Модуль выгружен\n");
}
