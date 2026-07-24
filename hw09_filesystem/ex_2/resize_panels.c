#include "eltex_commander.h"

int resize_panels(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel,
                  WINDOW *right_content) {
  int t_y, t_x;  //< Размеры основного окна (терминала)
  int ret = 0;

  clear();
  wclear(left_panel);
  wclear(right_panel);
  wclear(left_content);
  wclear(right_content);

  // Обрабатываем изменение размера терминала
  getmaxyx(stdscr, t_y, t_x);
  wresize(left_panel, t_y - TOPMENU_SIZE - STATUSBAR_SIZE, (t_x / 2));
  wresize(left_content, t_y - TOPMENU_SIZE - STATUSBAR_SIZE - 2, (t_x / 2) - 2);
  mvwin(right_panel, TOPMENU_SIZE, t_x / 2);
  mvwin(right_content, TOPMENU_SIZE + 1, (t_x / 2) + 1);
  // mvderwin не пересчитывает новые относительные координаты. Вместо этого,
  // дочернее окно как бы зависает на месте. А когда мы уменьшаем
  // размер терминала, то вообще дубликат дочернего окна вылезает слева.
  // Поэтому используем mvwin с абсолютными координатами.

  wresize(right_panel, t_y - TOPMENU_SIZE - STATUSBAR_SIZE, ((t_x + 1) / 2));
  wresize(right_content, t_y - TOPMENU_SIZE - STATUSBAR_SIZE - 2,
          ((t_x + 1) / 2) - 2);
  box(left_panel, ACS_VLINE, ACS_HLINE);
  box(right_panel, ACS_VLINE, ACS_HLINE);

  return ret;
}
