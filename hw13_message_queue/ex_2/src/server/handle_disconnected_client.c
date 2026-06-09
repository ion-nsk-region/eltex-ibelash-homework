#include "server.h"

void handle_disconnected_client(int client_mq_id, pid_t client,
                                struct user *users, int *n_users) {
  struct user *user = users;
  while (user - users < *n_users && user->pid != client) {
    ++user;
  }

  if (user->pid != client) {
    fprintf(stderr, "Предупреждение: пользователь с pid %d не найден.", client);
  } else {
    send_user_left_notification(client_mq_id, users, *n_users, user->nickname,
                                strlen(user->nickname));
    if (NULL != user->nickname) free(user->nickname);
    if (1 < *n_users) {  // заменяем искомого на последнего пользователя
      struct user *last_user = users + *n_users - 1;
      user->pid = last_user->pid;
      user->nickname = last_user->nickname;
      last_user->pid = 0;
      last_user->nickname = NULL;
    } else {  // единственный пользователь
      user->pid = 0;
      user->nickname = NULL;
    }

    --(*n_users);
    send_users_list(client_mq_id, users, *n_users);
  }
  // TODO удалить непрочитанные пользователем сообщения из очереди.
}
