#include "calc.h"

void run_operation(void *func_handles[FUNC_MAX], char *func_names[FUNC_MAX], int menu_item) {
    printf("Выполняем %s\n", menu_names[menu_item]);
    operation = dlsym(func_handles[menu_item], func_names[menu_item]);
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        continue;
    }
    (*operation)();
}
