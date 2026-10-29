#include "server.h"

void handle_disconnected_client(pid_t client, struct user *users,
                                int *n_users) {
  struct user *user = users;
  while (user - users < *n_users && user->pid != client) {
    ++user;
  }

  if (user->pid != client) {
    fprintf(stderr, "Предупреждение: пользователь с pid %d не найден.", client);
  } else {
    if (1 < *n_users) {  // заменяем искомого на последнего пользователя
      struct user *last_user = users + *n_users - 1;
      user->pid = last_user->pid;
      size_t nickname_len = strlen(last_user->nickname);
      strncpy(user->nickname, last_user->nickname, nickname_len);
      last_user->pid = 0;
      last_user->nickname[0] = '\0';
    } else {  // единственный пользователь
      user->pid = 0;
      user->nickname[0] = '\0';
    }

    --(*n_users);
  }
}
