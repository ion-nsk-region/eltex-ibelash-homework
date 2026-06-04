#include "mq_chat.h"

int send_user_joined_notification(int client_mq_id, struct user *users,
                                  int n_users, char *client_nickname,
                                  size_t client_nickname_length) {
  int err = 0;
  size_t user_joined_content_length =
      client_nickname_length + sizeof("Пользователь  присоединился к чату.");
  errno = 0;
  char *user_joined_content = malloc(user_joined_content_length);
  if (NULL == user_joined_content) {
    err = errno;
    perror("malloc");
  } else {
    snprintf(user_joined_content, user_joined_content_length,
             "Пользователь %s присоединился к чату.", client_nickname);
    struct chat_msg user_joined_msg = {getpid(), MSG, user_joined_content};
    msg_to_all(client_mq_id, user_joined_msg, users, n_users);
    free(user_joined_content);
  }

  return err;
}
