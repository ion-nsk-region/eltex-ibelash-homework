#include "mq_chat.h"
#define MAX_PID_STR_LENGTH 12

int send_users_list(int client_mq_id, long to_whom, struct user *users,
                    int n_users) {
  int err = 0;
  size_t max_msg_size = get_max_msg_size();

  errno = 0;
  char *buffer =
      malloc((max_msg_size - sizeof(struct chat_msg)) * sizeof(char));
  if (NULL == buffer) {
    err = errno;
    perror("malloc");
  }

  err = users_list_to_string(users, n_users, max_msg_size - sizeof(struct chat_msg), buffer);

  if (0 == err) {
    struct chat_msg msg;
    msg.sender = 1;
    msg.cmd = LIST;
    msg.content = buffer;
    send_mq_msg(client_mq_id, to_whom, msg);
  }

  return err;
}
