#include "eltex_commander.h"

int create_panels(WINDOW *stdscr, WINDOW **left_panel, WINDOW **right_panel) {
  int t_y, t_x;  //< Размеры основного окна (терминала)
                 
  getmaxyx(stdscr, t_y, t_x);
  *left_panel = derwin(stdscr, t_y - 2, (t_x / 2), 1, 0);
  if (NULL == *left_panel) {
    fprintf(stderr,
            "Не удалось создать левую панель.\n"
            "Выходим.\n");
    return -1;
  }

  *right_panel = derwin(stdscr, t_y - 2, (t_x / 2), 1, (t_x + 1) / 2);
  if (NULL == *right_panel) {
    fprintf(stderr,
            "Не удалось создать правую панель.\n"
            "Выходим.\n");
    return -1;
  }
  
  return 0; 
}
