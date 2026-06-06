#include "client_ui.h"

void handle_resize(struct ui ui) {
  int t_y, t_x;  //< Размеры основного окна (терминала)

  clear();
  wclear(ui.history);
  wclear(ui.users_list);
  wclear(ui.msg_input);

  // Обрабатываем изменение размера терминала
  getmaxyx(stdscr, t_y, t_x);
  int msg_input_height =
      (t_y * REL_MSG_INPUT_HEIGHT / 100) < MIN_MSG_INPUT_HEIGHT
          ? MIN_MSG_INPUT_HEIGHT
          : t_y * REL_MSG_INPUT_HEIGHT / 100;
  int top_height = t_y - msg_input_height;
  int history_width = t_x * REL_HISTORY_WIDTH / 100;
  int users_list_width = t_x - history_width;

  wresize(ui.history, top_height, history_width);

  mvwin(ui.users_list, 0, history_width);
  wresize(ui.users_list, top_height, users_list_width);
  mvwvline(ui.users_list, 0, 0, ACS_VLINE, top_height);

  mvwin(ui.msg_input, top_height, 0);
  wresize(ui.msg_input, msg_input_height, t_x);
  mvwhline(ui.msg_input, 0, 0, ACS_HLINE, t_x);
  mvwaddch(ui.msg_input, 0, history_width, ACS_BTEE);

  /*
  box(history, ACS_VLINE, ACS_HLINE);
  box(users_list, ACS_VLINE, ACS_HLINE);
  box(msg_input, ACS_VLINE, ACS_HLINE);
  */

}
