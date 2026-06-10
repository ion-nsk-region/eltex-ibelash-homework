#include "mq_chat.h"

char *pid_to_nick(struct user *users, int n_users, pid_t pid, int *free_nick) {
  char *nickname = NULL;
  *free_nick = 0;

  if (1 == pid) {  // server
    nickname = malloc(7);
    if (NULL != nickname) {
      *free_nick = 1;
      snprintf(nickname, 7, "server");
    }
  } else if (NULL == users || 0 >= n_users) {
    int nickname_length = snprintf(NULL, 0, "[%d]error", pid);
    nickname = malloc(nickname_length + 1);
    if (NULL != nickname) {
      *free_nick = 1;
      snprintf(nickname, nickname_length + 1, "[%d]error", pid);
    }
    fprintf(stderr,
            "Ошибка: Не найден ник пользователя %d.\n"
            "        Список участников чата пуст.\n",
            pid);
  } else {  // ищем по списку
    for (struct user *user = users; user - users < n_users; ++user) {
      if (pid == user->pid) nickname = user->nickname;
    }
  }

  if (NULL ==
      nickname) {  // отключился, битые данные, не удалось выделить память
    int nickname_length = snprintf(NULL, 0, "[%d]Not found", pid);
    nickname = malloc(nickname_length + 1);
    if (NULL != nickname) {
      *free_nick = 1;
      snprintf(nickname, nickname_length + 1, "[%d]Not found", pid);
    }

    fprintf(stderr,
            "Не найден ник пользователя %d.\n"
            "Пользователь уже отключился?!\n",
            pid);
  }

  return nickname;
}
