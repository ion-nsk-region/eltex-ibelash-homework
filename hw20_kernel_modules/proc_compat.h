#ifndef PROC_COMPAT_H
#define PROC_COMPAT_H

#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
    #define HAVE_PROC_OPS

    // макрос HAVE_PROC_OPS может быть определён и на старых ядрах при 
    // бэкпорте функциональности. Поэтому используем его, а не версию
    // ядря напрямую.
#endif

#ifdef HAVE_PROC_OPS
    // если где-то потребуется тип (proc_ops), то используем следующий макрос
#   define COMPAT_PROC_OPS struct proc_ops

    // а теперь сама структура
#   define DEFINE_COMPAT_PROC_OPS(name, read_fn, write_fn) \
            static const struct proc_ops name = { \
                    .proc_read = read_fn, \
                    .proc_write = write_fn, \
            }

#   define compat_proc_create(name, mode, parent, ops) \
            proc_create(name, mode, parent, ops)

#else // старые ядра без бэкпорта
    // если где-то потребуется тип структуры, то используем следующий макрос
#   define COMPAT_PROC_OPS struct file_operations

    // а теперь сама структура
#   define DEFINE_COMPAT_PROC_OPS(name, read_fn, write_fn) \
        static const struct file_operations name = { \
                .owner = THIS_MODULE, \
                .read = read_fn, \
                .write = write_fn, \
        }

#   define compat_proc_create(name, mode, parent, ops) \
            proc_create(name, mode, parent, ops)

#endif // HAVE_PROC_OPS

#endif // PROC_COMPAT_H

