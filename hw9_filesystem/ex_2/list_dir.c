#include <dirent.h>

#include "eltex_commander.h"

int list_dir(const char dir_path[PATH_MAX], WINDOW *panel) {
  struct dirent **namelist;
  int ret, n;

  n = scandir(dir_path, &namelist, NULL, alphasort);
  if (-1 == n) {
    perror("scandir");
    return -1;
  }

  for (int i = 0; i < n; i++) {
    // TODO выделить в отдельную функцию. Сейчас перечитывание директории 
    // с диска происходит на каждый чих - неэкономно. Лучше хранить 
    // прочитанную директорию в массиве строк. 
    ret = mvwprintw(panel, i, 0, "%s", namelist[i]->d_name);
    if (0 > ret) {
      // ошибка будет вываливаться каждый раз когда список файлов длиннее 
      // чем размер окна. Возможно здесь будет уместнее использовать пады.
      perror("mvwprintw");
      return -2;
    }
  }

  return 0;
}
