#include "eltex_commander.h"

void debug(const char *path, char *path_buffer) {
  if (NULL != path || NULL != path_buffer){
     mvprintw(0, 0, "Path %s Buffer %s", path, path_buffer);
  } else {
     mvprintw(0, 0, "It is NULL");
  }
}
/*
void debug(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel, WINDOW *right_content, int active_select) {
  int lp_y, lp_x, lc_y, lc_x, rp_y, rp_x, rc_y, rc_x;
  // выводим размеры терминала, левой и правой панели.
  getmaxyx(left_panel, lp_y, lp_x);
  getmaxyx(right_panel, rp_y, rp_x);
  getmaxyx(left_content, lc_y, lc_x);
  getmaxyx(right_content, rc_y, rc_x);
  mvprintw(0, 0, "L %dx%d(%dx%d)  R %dx%d(%dx%d) select %03d", lp_y, lp_x, lc_y, lc_x, rp_y, rp_x, rc_y, rc_x, active_select);
}
*/
