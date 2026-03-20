#include "eltex_commander.h"

int resize_panels(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel,
                  WINDOW *right_content) {
  int t_y, t_x;  //< Размеры основного окна (терминала)
  // char path_buffer[PATH_MAX];
  int ret = 0;
  clear();
  wclear(left_panel);
  wclear(right_panel);
  wclear(left_content);
  wclear(right_content);

  // Обрабатываем изменение размера терминала
  getmaxyx(stdscr, t_y, t_x);
  wresize(left_panel, t_y - 2, (t_x / 2));
  wresize(left_content, t_y - 4, (t_x / 2) - 2);
  mvwin(right_panel, 1, t_x / 2);
  mvwin(right_content, 2, (t_x / 2) + 1);
  // mvderwin не пересчитывает новые относительные координаты. Вместо этого,
  // дочернее окно как бы зависает на месте. А когда мы уменьшаем
  // размер терминала, то вообще дубликат дочернего окна вылезает слева.
  // Поэтому используем mvwin с абсолютными координатами.

  wresize(right_panel, t_y - 2, ((t_x + 1) / 2));
  wresize(right_content, t_y - 4, ((t_x + 1) / 2) - 2);
  box(left_panel, ACS_VLINE, ACS_HLINE);
  box(right_panel, ACS_VLINE, ACS_HLINE);

  return ret;
}
