#include "eltex_commander.h"

int create_panels(WINDOW *stdscr, WINDOW **left_panel, WINDOW **right_panel, WINDOW **left_content, WINDOW **right_content) {
  int t_y, t_x;  //< Размеры основного окна (терминала)
                 
  getmaxyx(stdscr, t_y, t_x);
  *left_panel = newwin(t_y - 2, (t_x / 2), 1, 0);
  if (NULL == *left_panel) {
    fprintf(stderr,
            "Не удалось создать окно левой панели.\n"
            "Выходим.\n");
    return -1;
  }
  *left_content = derwin(*left_panel, t_y - 4, (t_x / 2) - 2, 1, 1);
  if (NULL == *left_content) {
    fprintf(stderr,
            "Не удалось создать окно для содержимого левой панели.\n"
            "Выходим.\n");
    return -1;
  }

  *right_panel = newwin(t_y - 2, (t_x / 2), 1, (t_x + 1) / 2);
  if (NULL == *right_panel) {
    fprintf(stderr,
            "Не удалось создать окно правой панели.\n"
            "Выходим.\n");
    return -1;
  }
  *right_content = derwin(*right_panel, t_y - 4, (t_x / 2) - 2, 1, 1);
  if (NULL == *right_content) {
    fprintf(stderr,
            "Не удалось создать окно для содержимого правой панели.\n"
            "Выходим.\n");
    return -1;
  }
  
  return 0; 
}
