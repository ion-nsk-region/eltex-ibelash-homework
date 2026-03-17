#include "eltex_commander.h"

int print_dir(WINDOW *panel, struct dirent **namelist, int n_files) {
  int err = 0, panel_length;
  int cur_y = getcury(panel);
  
  panel_length = getmaxy(panel);
  for (int i = 0, ret = OK; i < n_files && OK == ret && i < panel_length; i++) {
    if (i == cur_y) {
      attron(COLOR_PAIR(2));
    }
    ret = mvwprintw(panel, i, 0, "%s", namelist[i]->d_name);
    
    if (i == cur_y) {
      attroff(COLOR_PAIR(2));
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
