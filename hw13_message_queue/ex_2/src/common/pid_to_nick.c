#include "mq_chat.h"

char *pid_to_nick(struct user *users, int n_users, pid_t pid) {
  char *nickname = NULL;

  for (struct user *user = users; user - users < n_users; ++user) {
    if (pid == user->pid) nickname = user->nickname;
  }

  if (NULL == nickname) {
    fprintf(stderr, "Пользователь с pid = %d не найден.\n", pid);
  }

  return nickname;
}
