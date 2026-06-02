#include "mq_chat.h"
#define MAX_PID_STR_LENGTH 12

int users_list_to_string(struct user *users, int n_users,
                         size_t max_buffer_size, char *buffer) {
  int err = 0;
  size_t bytes_available = max_buffer_size;

  if (NULL == buffer) {
    fprintf(stderr,
            "Ошибка: users_list_to_string не указан адрес результирующей "
            "строки.\n");
    err = -1;
  }

  // упаковываем список пользователей
  if (0 == err) {
    char *buf_ptr = buffer;
    for (struct user *user = users; user - users < n_users; ++user) {
      char pid_str[MAX_PID_STR_LENGTH] = "";
      snprintf(pid_str, MAX_PID_STR_LENGTH, "%d", user->pid);
      size_t pid_str_length = strlen(pid_str);
      size_t nickname_length = strlen(user->nickname);
      if (bytes_available > (pid_str_length + 1 + nickname_length + 1)) {
        memcpy(buf_ptr, pid_str, pid_str_length);
        buf_ptr += pid_str_length;
        *buf_ptr = 0x1F;  // Unit separator = разделитель полей
        ++buf_ptr;
        memcpy(buf_ptr, user->nickname, (nickname_length));
        buf_ptr = buf_ptr + nickname_length;
        *buf_ptr = 0x1E;  // Record separator = разделитель записей
        ++buf_ptr;
        bytes_available =
            bytes_available - (sizeof(pid_t) + 1) - (nickname_length + 1);
      } else {
        fprintf(stderr,
                "Ошибка: недостаточно места в буфере для полного списка "
                "пользователей.\n");
        err = -1;
      }
    }
  }

  return err;
}
