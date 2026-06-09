#include "client.h"

void update_users_list(WINDOW *users_list, char *content, struct user *users,
                       int *n_users) {
  pid_t pid_buf;
  int total_bytes_read = 0;
  int pid_bytes_read = 0;
  struct user *user = users;
  int users_list_width = getmaxx(users_list);
  *n_users = 0;

  if (NULL == content) {
    fprintf(stderr,
            "Ошибка: Не удалось загрузить список пользователей. Получено "
            "пустое сообщение от сервера.\n");
    wprintw(users_list,
            "Ошибка: Не удалось загрузить список пользователей. Получено "
            "пустое сообщение от сервера.\n");
  } else {
    char nickname[MAX_NICKNAME_LENGTH];
    char *ptr = content;
    while (2 == sscanf(ptr, "%d\x1F%n%255[^\x1E]\x1E%n", &pid_buf,
                       &pid_bytes_read, nickname, &total_bytes_read) &&
           MAX_CHAT_USERS > *n_users) {
      user->pid = pid_buf;
      int nickname_length = total_bytes_read - pid_bytes_read;
      if (NULL == user->nickname) user->nickname = malloc(nickname_length);
      if (NULL == user->nickname) {
        perror("malloc");
      } else {
        *(nickname + nickname_length) = '\0';
        strncpy(user->nickname, nickname, nickname_length);
        ++(*n_users);
      }

      ptr += total_bytes_read;
      ++user;
    }
  }

  int height = getmaxy(users_list);
  wmove(users_list, 0, 0);
  wclrtobot(users_list);
  mvwvline(users_list, 0, 0, ACS_VLINE, height);

  if (0 >= *n_users) {
    fprintf(stderr,
            "Ошибка: Не удалось загрузить список пользователей. Сообщение от "
            "сервера не было распознано.\n");
    wprintw(users_list,
            "Ошибка: Не удалось загрузить список пользователей. Сообщение от "
            "сервера не было распознано.\n");

  } else {
    for (user = users; user - users < *n_users; ++user) {
      mvwprintw(users_list, user - users, 1, "%d %.*s", user->pid,
                users_list_width - pid_bytes_read, user->nickname);
    }
  }
}
