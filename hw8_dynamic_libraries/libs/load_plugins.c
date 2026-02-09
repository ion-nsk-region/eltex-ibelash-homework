#include <stdlib.h>

#include "calc.h"

int load_plugins(void *func_handles[FUNC_MAX], char *func_names[FUNC_MAX],
                 char *menu_names[FUNC_MAX], int *n_items) {
  char *func_name, *menu_name;
  char path_buffer[266];  // "./plugins/" - 10 байт + 256 байт от d_name
  void *handle;
  unsigned int *menu_pos;
  struct dirent **namelist;
  int ret, n;

  *n_items = 0;

  n = scandir("./plugins", &namelist, filter_plugin_names, alphasort);
  if (n == -1) {
    perror("scandir");
    return -1;
  }

  while (n--) {
    sprintf(path_buffer, "./plugins/%s", namelist[n]->d_name);
    const char *plugin_path = path_buffer;
    ret = get_plugin_symbols(plugin_path, &handle, &func_name, &menu_name,
                             &menu_pos);
    if (0 == ret) {
      func_handles[*menu_pos] = handle;
      func_names[*menu_pos] = func_name;
      menu_names[*menu_pos] = menu_name;
      *n_items = *n_items + 1;
    } else {
      fprintf(stderr, "Плагин %s не был загружен. Код ошибки: %d\n",
              path_buffer, ret);
    }

    free(namelist[n]);
  }
  free(namelist);

  return 0;
}
