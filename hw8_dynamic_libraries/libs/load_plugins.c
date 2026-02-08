#include <stdlib.h>
#include "calc.h"

int load_plugins(void *func_handles[FUNC_MAX], char *func_names[FUNC_MAX],
                 char *menu_names[FUNC_MAX], int *n_items) {
  char *func_name, *menu_name, path_buffer[255];
  void *handle;
  unsigned int *menu_pos;
  struct dirent **namelist;
  int ret, n;

  /*
  for (int i = 0; i < FUNC_MAX; i++) {
      func_handles[i] = NULL;
      func_names[i] = NULL;
      menu_names[i] = NULL;
  }
  */

  *n_items = 0;

  n = scandir("./plugins", &namelist, filter_plugin_names, alphasort);
  if (n == -1) {
    perror("scandir");
    return -1;
  }

  while (n--) {
    printf("./plugins/%s\n", namelist[n]->d_name);
    sprintf(path_buffer, "./plugins/%s", namelist[n]->d_name);
    const char *plugin_path = path_buffer;
    ret = get_plugin_symbols(plugin_path, &handle, &func_name, &menu_name,
                             &menu_pos);
    if (0 == ret) {
      func_handles[*menu_pos] = handle;
      func_names[*menu_pos] = func_name;
      menu_names[*menu_pos] = menu_name;
    }
    free(namelist[n]);
  }
  free(namelist);

  *n_items = *n_items + 1;

  return 0;
}
