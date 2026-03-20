#include "eltex_commander.h"

int list_dir(char dir_path[PATH_MAX], struct dirent ***namelist, int *n_files) {
  int ret = 0;
  const char *path = dir_path;

  *n_files = scandir(path, namelist, NULL, alphasort);
  if (-1 == *n_files) {
    perror("scandir");
    ret = -1;
  }

  return ret;
}
