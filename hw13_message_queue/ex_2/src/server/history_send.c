#include "mq_chat.h"

int history_send(int client_mq_id, long to_whom, struct chat_msg *history,
                 int last_msg_id) {
  int err = 0, err_packing = 0;
  size_t buffer_size = get_max_msg_size() - sizeof(struct chat_msg);

  int start_msg_id;
  if (NO_COMMAND == (history + last_msg_id + 1)->cmd) {
    start_msg_id = 0;
  } else {
    start_msg_id = (last_msg_id + 1) % MAX_HISTORY_SIZE;
  }

  errno = 0;
  char *buffer = (char *)malloc(buffer_size);
  if (NULL == buffer) {
    err = errno;
    perror("malloc");
  }

  do {
    if (0 == err) {
      if (ERANGE == err_packing) {
        int n_attempts = 0;
        while (0 == is_mq_empty(client_mq_id, NULL) &&
               ETIME !=
                   conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME, ++n_attempts));
      }
      err_packing = history_to_string(history, &start_msg_id, last_msg_id,
                                      buffer, buffer_size);
      struct chat_msg msg;
      msg.sender = 1;
      msg.cmd = HISTORY;
      msg.content = buffer;
      err = send_mq_msg(client_mq_id, to_whom, msg);
    }
  } while (ERANGE == err_packing && 0 == err);

  if (NULL != buffer) free(buffer);

  return err;
}
