#include "shm_chat.h"

int pid_to_nick(struct user *users, int n_users, pid_t pid, char *nickname) {
  int err = 0;
  if (NULL == users || NULL == nickname) {
    err = -1;
    return err;
  }

  if (1 == pid) {  // server
    snprintf(nickname, 7, "server");
  } else if (0 >= n_users) {
    int nickname_length = snprintf(NULL, 0, "[%d]error", pid);
    snprintf(nickname, nickname_length + 1, "[%d]error", pid);
    fprintf(stderr,
            "Ошибка: Не найден ник пользователя %d.\n"
            "        Список участников чата пуст.\n",
            pid);
  } else {  // ищем по списку
    for (struct user *user = users; user - users < n_users; ++user) {
      if (pid == user->pid)
        snprintf(nickname, strlen(user->nickname), "%s", user->nickname);
    }
  }

  if ('\0' == nickname[0]) {  // отключился, битые данные
    int nickname_length = snprintf(NULL, 0, "[%d]Not found", pid);
    snprintf(nickname, nickname_length + 1, "[%d]Not found", pid);

    fprintf(stderr,
            "Не найден ник пользователя %d.\n"
            "Пользователь уже отключился?!\n",
            pid);
  }

  return err;
}
