#include "eltex_commander.h"

int list_dir(const char dir_path[PATH_MAX], struct dirent **namelist, int *n_files) {
  int ret = 0;

  *n_files = scandir(dir_path, &namelist, NULL, alphasort);
  if (-1 == *n_files) {
    perror("scandir");
    ret = -1;
  }
    /*
    ret = mvwprintw(panel, i, 0, "%s", namelist[i]->d_name);
    if (0 > ret) {
      // ошибка будет вываливаться каждый раз когда список файлов длиннее 
      // чем размер окна. Возможно здесь будет уместнее использовать пады.
      perror("mvwprintw");
      return -2;
    }
    */

  return ret;
}
