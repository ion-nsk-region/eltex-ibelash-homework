#include <dlfcn.h>
#include "calc.h"

void run_operation(void *func_handle, char *func_name) {
    char *error;
    void (*operation)(void);

    operation = dlsym(func_handle, func_name);
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        return;
    }
    (*operation)();
}
