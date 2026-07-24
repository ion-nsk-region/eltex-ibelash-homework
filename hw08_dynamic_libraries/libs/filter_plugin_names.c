#include <dirent.h>
#include <string.h>

int filter_plugin_names(const struct dirent *entry) {
  int len = strlen(entry->d_name);
  const char *extension = &(entry->d_name[len - 3]);

  // Ищем совпадения с шаблоном lib*.so
  if (0 == strncmp(entry->d_name, "lib", 3) &&
      0 == strncmp(extension, ".so", 3)) {
    return 1;
  }
  return 0;
}
