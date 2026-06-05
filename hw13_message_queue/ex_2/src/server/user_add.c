#include "mq_chat.h"

int user_add(pid_t pid, const char *nickname, size_t nickname_length,
             struct user *users, int *n_users) {
  int err = 0;

  if (MAX_CHAT_USERS > *n_users) {
    struct user *user = users + *n_users;
    errno = 0;
    user->nickname = malloc((nickname_length + 1) * sizeof(char));
    if (NULL == user->nickname) {
      err = errno;
      perror("malloc");
    } else {
      // Собственно добавляем:
      strncpy(user->nickname, nickname, nickname_length + 1);
      user->pid = pid;
      ++(*n_users);
    }
  } else {
    fprintf(stderr,
            "Ошибка: невозможно добавить пользователя. Чат переполнен.\n");
    err = -1;
  }

  return err;
}
