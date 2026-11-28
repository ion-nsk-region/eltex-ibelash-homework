#include <stddef.h>

#include "client.h"

void on_key_enter(struct chat_msg *input, sem_t *input_updated,
                  sem_t *input_read, WINDOW *input_window, char *input_buf,
                  size_t *input_buf_length) {
  if (0 < *input_buf_length) {
    struct chat_msg msg;
    msg.sender = getpid();
    msg.cmd = MSG;
    msg.msg_size = offsetof(struct chat_msg, content) + *input_buf_length;
    strncpy(msg.content, input_buf, *input_buf_length);

    int err;
    err = send_msg(input, &msg, input_updated, input_read);
    if (0 != err) {
      printf("Ошибка send_msg: %d\n", err);
    }

    wmove(input_window, 1, 0);
    wclrtobot(input_window);
    *input_buf_length = 0;
    *input_buf = '\0';
  }
}
