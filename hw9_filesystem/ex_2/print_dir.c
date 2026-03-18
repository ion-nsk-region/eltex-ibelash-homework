#include "eltex_commander.h"

int print_dir(WINDOW *panel, struct dirent **namelist, int n_files, int select) {
  int err = 0, panel_length, offset = 0, is_active = 0;
  wclear(panel);  // вызывает мерцание, но без этого остаются артефакты от длинных имён
  panel_length = getmaxy(panel) - 1;
    if (0 <= select) {
        is_active = 1;
    } else {
        select = -select;
    }

  if(select > panel_length) {
    offset = select - panel_length;
    select = panel_length;
  }
  for (int i = 0, ret = OK; i + offset < n_files  && OK == ret && i - offset <= panel_length; i++) {
    if (i == select && is_active) {
      wattron(panel, A_REVERSE);
    }
    ret = mvwprintw(panel, i, 0, "%s", namelist[i + offset]->d_name);
    
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
