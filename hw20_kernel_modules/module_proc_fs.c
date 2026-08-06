#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock.h>

#include "proc_compat.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, обменивающийся информацией через proc_fs.");
MODULE_VERSION("1.0");

#define MAX_STR_SIZE 30
#define FILENAME "module_proc_fs"
#define FILE_PTR module_proc_fs

static rwlock_t lock;
static char a_string[MAX_STR_SIZE] = "Здравствуйте!";
static struct proc_dir_entry *FILE_PTR = NULL;

static ssize_t read_from_proc_fs(struct file *fd, char __user *buf, size_t size,
                                 loff_t *offset) {
  ssize_t bytes_read, a_string_length = strnlen(a_string, MAX_STR_SIZE - 1);

  if (*offset >= a_string_length)  // данные уже прочитали
    return 0;

  read_lock(&lock);
  bytes_read =
      simple_read_from_buffer(buf, size, offset, a_string, a_string_length);
  read_unlock(&lock);

  return bytes_read;
}

static ssize_t write_to_proc_fs(struct file *fd, const char __user *buf,
                                size_t size, loff_t *offset) {
  ssize_t bytes_written;

  if (MAX_STR_SIZE < size) return -EINVAL;

  write_lock(&lock);
  bytes_written =
      simple_write_to_buffer(a_string, MAX_STR_SIZE, offset, buf, size);
  if ('\n' == *(a_string + size - 1)) {
    *(a_string + size - 1) = '\0';
  } else {
    *(a_string + size) = '\0';
  }
  write_unlock(&lock);

  return bytes_written;
}

// макрос разворачивается в зависимости от наличия поддержки структуры proc_ops
// см. подробности в proc_compat.h
DEFINE_COMPAT_PROC_OPS(fops, read_from_proc_fs, write_to_proc_fs);

static int __init module_proc_fs_init(void) {
  int err = 0;

  rwlock_init(&lock);

  FILE_PTR = compat_proc_create(FILENAME, 0666, NULL, &fops);

  if (NULL == FILE_PTR) {
    err = -ENOMEM;
    pr_err("Ошибка: не удалось создать файл /proc/%s, код ошибки: %d\n",
           FILENAME, err);
  } else {
    pr_info("Модуль загружен\n");
  }

  return err;
}

static void __exit module_proc_fs_exit(void) {
  proc_remove(FILE_PTR);
  pr_info("Модуль выгружен\n");
}

module_init(module_proc_fs_init);
module_exit(module_proc_fs_exit);
