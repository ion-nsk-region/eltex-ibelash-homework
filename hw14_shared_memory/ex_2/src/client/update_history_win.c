#include "client.h"

void update_history_win(WINDOW *history, char *content, struct user *users,
                        int n_users) {
  if (NULL == content) {
    fprintf(stderr,
            "Ошибка: Не удалось загрузить историю. Получено пустое сообщение "
            "от сервера.\n");
    wprintw(history,
            "Ошибка: Не удалось загрузить историю. Получено пустое сообщение "
            "от сервера.\n");
  } else if (NULL == users || 0 >= n_users) {
    fprintf(
        stderr,
        "Ошибка: Не удалось загрузить историю. Список пользователей пуст.\n");
    wprintw(
        history,
        "Ошибка: Не удалось загрузить историю. Список пользователей пуст.\n");
  } else {
    pid_t pid_buf = -1;
    size_t buffer_size = get_max_msg_size() - sizeof(struct chat_msg);
    char *buffer = malloc(buffer_size);
    if (NULL != buffer) {
      enum chat_command cmd = 0;
      int first_bytes_read = 0, total_bytes_read = 0, free_nick = 0;
      char *ptr = content, *nickname = NULL;
      char format[25];
      // делаем следующую строку формата "%d\x1F%d\x1F%n%8???[^\x1E]\x1E%n"
      snprintf(format, sizeof(format), "%%d\x1F%%d\x1F%%n%%%zu[^\x1E]\x1E%%n",
               buffer_size - 1);
      while ('\0' != *ptr) {
        int items = sscanf(ptr, format, &pid_buf, &cmd, &first_bytes_read,
                           buffer, &total_bytes_read);
        if (2 == items && '\x1E' == *(ptr + first_bytes_read)) {
          ptr = ptr + first_bytes_read + 1;
        } else if (3 == items) {
          ptr += total_bytes_read;
        } else {
          fprintf(stderr,
                  "Ошибка: не удалось прочитать запись.\n"
                  "Шагаем по байту, пока не выйдем на валидную запись.\n");
          while (!('\x1E' == *ptr || '\0' == *ptr)) {
            ++ptr;
          }
        }
        if (MSG == cmd && 3 == items) {  // печатаем только сообщения.
          nickname = pid_to_nick(users, n_users, pid_buf, &free_nick);
          wprintw(history, "%s: %s\n", nickname, buffer);
          if (free_nick) free(nickname);
        }
      }  // while
      free(buffer);
    } else {
      perror("malloc");
    }
  }
}
