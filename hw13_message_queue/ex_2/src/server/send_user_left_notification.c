#include "server.h"

int send_user_left_notification(int client_mq_id, struct user *users,
                                int n_users, const char *client_nickname,
                                size_t client_nickname_length) {
  int err = 0;
  size_t user_left_content_length =
      client_nickname_length + sizeof("Пользователь  покинул чат.");
  errno = 0;
  char *user_left_content = malloc(user_left_content_length);
  if (NULL == user_left_content) {
    err = errno;
    perror("malloc");
  } else {
    snprintf(user_left_content, user_left_content_length,
             "Пользователь %s покинул чат.", client_nickname);
    struct chat_msg user_left_msg = {getpid(), MSG, user_left_content};
    msg_to_all(client_mq_id, user_left_msg, users, n_users);
    free(user_left_content);
  }

  return err;
}
