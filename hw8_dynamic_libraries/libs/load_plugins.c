#include <dlfcn.h>
#include "calc.h"

int load_plugins(
                void *func_handles[FUNC_MAX], 
                char *func_names[FUNC_MAX], 
                char *menu_names[FUNC_MAX], 
                int *n_items) {
    char *error;
    void *handle;
    unsigned int *menu_pos;

    dlerror(); // Очищаем сообщения об ошибках
    *n_items = 0;

    handle = dlopen("./libs/libadd.so", RTLD_NOW);
    //handle = dlopen(plugin_path, RTLD_NOW);
    error = dlerror();
    if (NULL == handle && NULL != error) {
        fprintf(stderr, "%s\n", error);
        return -1;
    }
    
    menu_pos = (unsigned int *)dlsym(handle, "menu_pos");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        return -2;
    }

    func_handles[*menu_pos] = handle;

    func_names[*menu_pos] = dlsym(handle, "func_name");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        return -3;
    }
    
    menu_names[*menu_pos] = dlsym(handle, "menu_name");
    error = dlerror();
    if (NULL != error) {
        fprintf(stderr, "%s\n", error);
        return -4;
    }

    *n_items = *n_items + 1;

    return 0;
}
