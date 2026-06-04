#include "mq_chat.h"

int send_users_list(int client_mq_id, long to_whom, struct user *users,
                    int n_users) {
  int err = 0;
  size_t content_size = get_max_msg_size() - sizeof(struct chat_msg);

  errno = 0;
  char *buffer = (char *)malloc(content_size);
  if (NULL == buffer) {
    err = errno;
    perror("malloc");
  } else {
    err = users_list_to_string(users, n_users, buffer, content_size);
  }

  if (0 == err) {
    struct chat_msg msg;
    msg.sender = 1;
    msg.cmd = LIST;
    msg.content = buffer;
    err = send_mq_msg(client_mq_id, to_whom, msg);
  }

  if (NULL != buffer) free(buffer);

  return err;
}
