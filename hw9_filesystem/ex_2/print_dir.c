// #include <sys/stat.h>

#include "eltex_commander.h"

int print_dir(WINDOW *panel, struct dirent **namelist, int n_files,
              int select) {
  if (NULL == panel || NULL == namelist) {
    fprintf(stderr, "Ошибка: print_dir - получен нулевой указатель.\n");
    return -1;
  }
  int err = 0, panel_length, panel_width, offset = 0, is_active = 0;
  panel_length = getmaxy(panel) - 1;
  panel_width = getmaxx(panel);

  // Если select < 0, то панель неактивна.
  if (0 <= select) {
    is_active = 1;
  } else {
    select = -select;
  }

  if (select > panel_length) {
    offset = select - panel_length;
    select = panel_length;
  }

  // очищаем содержимое, чтобы избавиться от артефактов.
  wmove(panel, 0, 0);
  wclrtobot(panel);

  for (int i = 0, ret = OK;
       i + offset < n_files && OK == ret && i <= panel_length; i++) {
    unsigned char filetype = namelist[i + offset]->d_type;
    if (DT_UNKNOWN == filetype) {
      status_bar(
          "Не удалось определить тип файла. "
          "Подробности в stderr.");
      fprintf(stderr, "Не удалось определить тип файла для %s",
              namelist[i + offset]->d_name);
      /*
      // TODO определяем тип файла через stat,
      // если scandir не смогла получить эту информацию.
      // TODO Выделить в функцию.

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
      */
    }

    if (i == select && is_active) {
      wattron(panel, A_REVERSE);
    }
    // TODO По идее, печать с форматированием строки надо выделить в функцию
    // TODO добавить вывод размера и времени изменения файла
    int width_name = panel_width - 2;
    if (DT_DIR == filetype) {
      ret = mvwprintw(panel, i, 0, "/%.*s", width_name,
                      namelist[i + offset]->d_name);
    } else if (DT_REG == filetype) {
      ret = mvwprintw(panel, i, 0, " %.*s", width_name,
                      namelist[i + offset]->d_name);
    } else {
      // TODO добавить обработку других известных типов файлов
      ret = mvwprintw(panel, i, 0, "?%.*s", width_name,
                      namelist[i + offset]->d_name);
    }
    if (ERR == ret) {
      // perror("mvwprintw");
      perror(namelist[i + offset]->d_name);
      err = -1;
    }
    if (i == select && is_active) {
      wattroff(panel, A_REVERSE);
    }
  }
  return err;
}
