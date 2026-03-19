#include <sys/stat.h>

#include "eltex_commander.h"

int print_dir(WINDOW *panel, struct dirent **namelist, int n_files,
              int select) {
        if (NULL == panel || NULL == namelist) {
            fprintf(stderr, "Ошибка: print_dir - получен нулевой указатель.\n");
            return -1;
        }
  int err = 0, panel_length, offset = 0, is_active = 0;
  wclear(panel);  // вызывает мерцание, но без этого остаются артефакты от
                  // длинных имён
  panel_length = getmaxy(panel) - 1;
  if (0 <= select) {
    is_active = 1;
  } else {
    select = -select;
  }

  if (select > panel_length) {
    offset = select - panel_length;
    select = panel_length;
  }
  for (int i = 0, ret = OK;
       i + offset < n_files && OK == ret && i - offset <= panel_length; i++) {
    unsigned char filetype = namelist[i + offset]->d_type;
    /*
    // TODO определяем тип файла через stat, 
    // если scandir не смогла получить эту информацию. 
    // TODO Выделить в функцию.

    if (DT_UNKNOWN == filetype) {
      struct stat stat_buf;
      char filepath[PATH_MAX];
      sprintf(filepath, "%s/%s", dirpath, namelist[i + offset]->d_name);
      lstat(filepath, &stat_buf);
      switch(stat_buf.st_mode & S_IFMT) {
          case S_IFREG: filetype = DT_REG; break;
          case S_IFDIR: filetype = DT_DIR; break;
          case S_IFLNK: filetype = DT_LNK; break;
          default: filetype = 0;
      }
    }
    */
    if (i == select && is_active) {
      wattron(panel, A_REVERSE);
    }
    if (DT_DIR == filetype) {
      ret = mvwprintw(panel, i, 0, "/%s", namelist[i + offset]->d_name);
    } else if (DT_REG == filetype) {
      ret = mvwprintw(panel, i, 0, " %s", namelist[i + offset]->d_name);
    } else {
      ret = mvwprintw(panel, i, 0, "?%s", namelist[i + offset]->d_name);
    }
    if (i == select && is_active) {
      wattroff(panel, A_REVERSE);
    }

    if (ERR == ret) {
      // ошибка будет вываливаться каждый раз когда список файлов длиннее
      // чем размер окна. Возможно здесь будет уместнее использовать пады.
      perror("mvwprintw");
      err = -1;
    }
  }
  return err;
}
