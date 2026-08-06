// Добавляем имя модуля ко всем сообщениям
// https://www.kernel.org/doc/html/latest/core-api/printk-basics.html#c.pr_fmt
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, выводящий сообщения о своей загрузке и выгрузке.");
MODULE_VERSION("1.0");

static int module_pr_info_init(void) {
  pr_info("Модуль загружен\n");

  return 0;
}

static void module_pr_info_exit(void) { pr_info("Модуль выгружен\n"); }

module_init(module_pr_info_init);
module_exit(module_pr_info_exit);
