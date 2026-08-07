#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, обменивающийся информацией через sys_fs.");
MODULE_VERSION("1.0");

#define MAX_STR_SIZE 30
#define DIRNAME "module_sys_fs"
#define DIR_PTR module_sys_fs
#define FILENAME a_string

static rwlock_t lock;
static char a_string[MAX_STR_SIZE] = "Здравствуйте!";
static struct kobject *DIR_PTR = NULL;

static ssize_t read_from_sys_fs(struct kobject *kobj,
                                struct kobj_attribute *attr, char __user *buf) {
  ssize_t bytes_read;

  read_lock(&lock);
  bytes_read = sysfs_emit(buf, "%s\n", a_string);
  read_unlock(&lock);

  return bytes_read;
}

static ssize_t write_to_sys_fs(struct kobject *kobj,
                               struct kobj_attribute *attr,
                               const char __user *buf, size_t size) {
  ssize_t bytes_written;
  loff_t pos = 0;

  if (MAX_STR_SIZE < size) return -EINVAL;

  write_lock(&lock);
  bytes_written =
      simple_write_to_buffer(a_string, MAX_STR_SIZE, &pos, buf, size);
  if ('\n' == *(a_string + size - 1)) {
    *(a_string + size - 1) = '\0';
  } else {
    *(a_string + size) = '\0';
  }
  write_unlock(&lock);

  return bytes_written;
}

static struct kobj_attribute string_attribute =
    __ATTR(a_string, 0644, read_from_sys_fs, write_to_sys_fs);

static struct attribute *attrs[] = {
    &string_attribute.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int __init module_sys_fs_init(void) {
  int err;

  rwlock_init(&lock);

  DIR_PTR = kobject_create_and_add(DIRNAME, kernel_kobj);

  if (NULL == DIR_PTR) {
    err = -ENOMEM;
    pr_err(
        "Ошибка: не удалось создать директорию /sys/kernel/%s, код ошибки: "
        "%d\n",
        DIRNAME, err);
    goto err_kobject_create;
  }

  err = sysfs_create_group(DIR_PTR, &attr_group);

  if (0 != err) {
    pr_err(
        "Ошибка: не удалось создать файл /sys/kernel/%s/a_string, код ошибки: "
        "%d\n",
        DIRNAME, err);
    goto err_sysfs_create_group;
  } else {
    pr_info("Модуль загружен\n");
  }

  return 0;

err_sysfs_create_group:
  kobject_put(DIR_PTR);

err_kobject_create:

  return err;
}

static void __exit module_sys_fs_exit(void) {
  kobject_put(DIR_PTR);
  pr_info("Модуль выгружен\n");
}

module_init(module_sys_fs_init);
module_exit(module_sys_fs_exit);
