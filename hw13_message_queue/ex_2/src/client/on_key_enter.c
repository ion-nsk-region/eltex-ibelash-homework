#include "client.h"

void on_key_enter(struct ui ui, int server_mq_id, char *input_buf,
                  size_t *input_buf_length) {
  if (0 < *input_buf_length) {
    pid_t my_pid = getpid();
    struct chat_msg my_msg = {my_pid, MSG, input_buf};
    int err;
    if (0 != (err = send_mq_msg(server_mq_id, 1, my_msg))) {
      printf("Ошибка send_mq_msg: %d\n", err);
    }
    wmove(ui.msg_input, 1, 0);
    wclrtobot(ui.msg_input);
    *input_buf_length = 0;
    *input_buf = '\0';
  }
}
