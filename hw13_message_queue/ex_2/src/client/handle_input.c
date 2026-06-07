#include <wctype.h>

#include "client.h"

void handle_input(WINDOW *msg_input_win, int server_mq_id, int ch,
                  char *input_buf) {
        int err = 0;
  switch (ch) {
    case KEY_ENTER:
      pid_t my_pid = getpid();
      struct chat_msg my_msg = {my_pid, MSG, input_buf};
      if (0 != (err = send_mq_msg(server_mq_id, 1, my_msg))) {
        printf("Ошибка send_mq_msg: %d\n", err);
      }
      werase(msg_input_win);
      wmove(msg_input_win, 1, 0);
      break;
    default:
      if (iswprint(ch)) {
        // wprintw(msg_input_win, "%lc", ch);
        waddch(msg_input_win, ch);
        // Добавить в буфер сообщения для отправки
        // char mb_char[5];
      }
  }
}
