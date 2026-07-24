#include "eltex_commander.h"

void status_bar(char *message) {
  int t_y = getmaxy(stdscr);
  move(t_y - STATUSBAR_SIZE, 0);
  wclrtobot(stdscr);
  mvwprintw(stdscr, t_y - STATUSBAR_SIZE, 0, "%s", message);
}
