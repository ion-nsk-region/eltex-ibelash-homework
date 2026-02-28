#include "eltex_commander.h"

void resize_panels(WINDOW *left_panel, WINDOW *right_panel) {
  int t_y, t_x,  //< Размеры основного окна (терминала)
      lp_y, lp_x,  //< Размеры левой панели
      rp_y, rp_x;  //< Размеры правой панели
  clear();

  // Обрабатываем изменение размера терминала
  getmaxyx(stdscr, t_y, t_x);
  wresize(left_panel, t_y - 2, (t_x / 2));
  mvderwin(right_panel, 1, t_x / 2);
  wresize(right_panel, t_y - 2, ((t_x + 1) / 2));
  box(left_panel, ACS_VLINE, ACS_HLINE);
  box(right_panel, ACS_VLINE, ACS_HLINE);

  // выводим размеры терминала, левой и правой панели.
  getmaxyx(left_panel, lp_y, lp_x);
  getmaxyx(right_panel, rp_y, rp_x);
  mvprintw(0, 0, "%dx%d  L %dx%d  R %dx%d", t_y, t_x, lp_y, lp_x, rp_y, rp_x);
}
