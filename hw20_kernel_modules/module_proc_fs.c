#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rwlock.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Модуль, обменивающийся информацией через proc_fs.");
MODULE_VERSION("1.0");

#define MAX_STR_SIZE 30
#define DIRECTORY "module_proc_fs"

static rwlock_t lock;
static char a_string[MAX_STR_SIZE] = "Здравствуйте!";

static ssize_t read_from_proc_fs(struct file *fd, char __user *buf, size_t size, loff_t *offset) {
    ssize_t bytes_read, a_string_length = strnlen(a_string, MAX_STR_SIZE - 1);

    if (*offset >= a_string_length) // данные уже прочитали
            return 0;

    read_lock(&lock);
    bytes_read = simple_read_from_buffer(buf, size, offset, a_string, a_string_length);
    read_unlock(&lock);

    return bytes_read;
}

static ssize_t write_to_proc_fs(struct file *fd, const char __user *buf, size_t size, loff_t *offset) {
    ssize_t bytes_written;

    if (MAX_STR_SIZE < size) 
            return -EINVAL;

    write_lock(&lock);
    bytes_written = simple_write_to_buffer(a_string, MAX_STR_SIZE, offset, buf, size);
    if ('\n' == *(a_string + size -1)) {
        *(a_string + size - 1) = '\0';
    } else {
        *(a_string + size) = '\0';
    }
    write_unlock(&lock);

    return bytes_written;
}
