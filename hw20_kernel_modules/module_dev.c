#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/rwlock.h>
#include <linux/version.h>
#include <linux/uaccess.h> // ?

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, обменивающийся информацией через файл устройства.");
MODULE_VERSION("1.0");

#define MAX_STR_SIZE 15
#define DEVICE_NAME "module_dev"

static int major_number = 0;
static rwlock_t lock;
static char test_string[MAX_STR_SIZE] = "Привет!\n\0";
static struct class *device_class;
static struct device *device_ptr;

ssize_t read_from_dev(struct file *fd, char __user *buff, size_t size, loff_t *off) {
    size_t bytes_read;

    read_lock(&lock);
    bytes_read = simple_read_from_buffer(buff, size, off, test_string, MAX_STR_SIZE);
    read_unlock(&lock);

    return bytes_read;
}

ssize_t write_to_dev(struct file *fd, const char __user *buff, size_t size, loff_t *off) {
    size_t bytes_written = 0;
    if (MAX_STR_SIZE < size) return -EINVAL;

    write_lock(&lock);
    bytes_written = simple_write_to_buffer(test_string, MAX_STR_SIZE, off, buff, size);
    write_unlock(&lock);

    return bytes_written;
}


static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_from_dev,
    .write = write_to_dev
};

// подсмотрено в ./fs/pstore/pmsg.c
static char *device_class_devnode(const struct device *dev, umode_t *mode) {
    if (mode) {
        *mode = 0666;
    }
    return NULL;
}

int init_module(void) {
    int err = 0;
    rwlock_init(&lock);
    
    major_number = register_chrdev(major_number, DEVICE_NAME, &fops);
    if (0 > major_number) {
        pr_err("Ошибка: не удалось зарегистрировать устройство, код ошибки: %d\n", major_number);
        return major_number; // ну тут у меня сдвиг парадигмы пошёл.
    } 
    pr_info("Получен основной номер устройства %d\n", major_number);

    // идея с условной компиляцией взята отсюда: https://sysprog21.github.io/lkmpg/#chardevc
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
    device_class = class_create(DEVICE_NAME);
#else
    device_class = class_create(THIS_MODULE, DEVICE_NAME);
#endif    
    if (IS_ERR(device_class)) {
        err = PTR_ERR(device_class);
        pr_err("Ошибка: не удалось создать класс устройства, код ошибки: %d\n", err);
        goto err_chrdev;
    }

    // устанавливаем права доступа
    device_class->devnode = device_class_devnode;

    // собственно, создаём устройство
    device_ptr = device_create(device_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(device_ptr)) {
        err = PTR_ERR(device_ptr);
        pr_err("Ошибка: не удалось создать устройство, код ошибки: %d\n", err);
        goto err_device_class;
    }
    pr_info("Создан файл устройства /dev/%s\n", DEVICE_NAME);

    pr_info("Модуль загружен\n");

    return 0;

// очистка выделенных ресурсов в случае ошибки
    
err_device_class:
    class_destroy(device_class);

err_chrdev:
    unregister_chrdev(major_number, DEVICE_NAME);

    return err;
}

void cleanup_module(void) {
    device_destroy(device_class, MKDEV(major_number, 0));
    class_destroy(device_class);
    unregister_chrdev(major_number, DEVICE_NAME);

    pr_info("Модуль выгружен\n");
}
