#include "calc.h"

int get_plugin_symbols(char *plugin_path, void **handle, char **func_name, char **menu_name, unsigned int **menu_pos) {
    char *error;
    dlerror(); // Очищаем сообщения об ошибках

    *handle = dlopen(plugin_path, RTLD_NOW);
    error = dlerror();
    if (NULL == *handle && NULL != error) {
        fprintf(stderr, "%s\n", error);
        return -1;
    }
    
    *menu_pos = (unsigned int *)dlsym(*handle, "menu_pos");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        dlclose(*handle);
        return -2;
    }

    if (FUNC_MAX < **menu_pos || 0 == **menu_pos) {
        fprintf(stderr, "Ошибка: Плагин %s декларирует позицию меню %u\n"
                        "Это за пределами доступных значений 1..%d", 
                        plugin_path, **menu_pos, (FUNC_MAX - 1));
        return -3;
    }

    *func_name = dlsym(*handle, "func_name");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        dlclose(*handle);
        return -4;
    }
    
    *menu_name = dlsym(*handle, "menu_name");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        dlclose(*handle);
        return -5;
    }

    return 0;
}
