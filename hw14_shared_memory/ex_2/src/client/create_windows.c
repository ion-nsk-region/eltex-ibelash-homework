#include "client_ui.h"

int create_windows(struct ui *ui) {
  int err = 0;
  int t_y, t_x;  //< Размеры основного окна (терминала)

  getmaxyx(stdscr, t_y, t_x);
  int msg_input_height =
      (t_y * REL_MSG_INPUT_HEIGHT / 100) < MIN_MSG_INPUT_HEIGHT
          ? MIN_MSG_INPUT_HEIGHT
          : t_y * REL_MSG_INPUT_HEIGHT / 100;
  int top_height = t_y - msg_input_height;
  int history_width = t_x * REL_HISTORY_WIDTH / 100;
  int users_list_width = t_x - history_width;

  ui->history = newwin(top_height, history_width, 0, 0);
  if (NULL == ui->history) {
    fprintf(stderr, "Не удалось создать окно с историей сообщений.\n");
    err = -1;
  } else {
    scrollok(ui->history, TRUE);  // включаем cкролинг содержимого
  }

  ui->users_list = newwin(top_height, users_list_width, 0, history_width);
  if (NULL == ui->users_list) {
    fprintf(stderr, "Не удалось создать окно со списком пользователей.\n");
    err = -1;
  }

  ui->msg_input = newwin(msg_input_height, t_x, top_height, 0);
  if (NULL == ui->msg_input) {
    fprintf(stderr, "Не удалось создать окно для ввода сообщения.\n");
    err = -1;
  } else {
    keypad(ui->msg_input, TRUE);
  }

  return err;
}
