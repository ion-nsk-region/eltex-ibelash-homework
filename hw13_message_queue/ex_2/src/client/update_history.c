#include "client.h"

void update_history_win(WINDOW *history, char *content, struct user *users,
                        int n_users) {
  if (NULL != users && 0 < n_users) {
    ;
  }
  if (NULL != content) {
    pid_t pid_buf;
    size_t buffer_size = get_max_msg_size() - sizeof(struct chat_msg);
    char *buffer = malloc(buffer_size);
    if (NULL != buffer) {
      enum chat_command cmd = 0;
      int total_bytes_read = 0;
      char *ptr = content;
      char format[35];
      snprintf(format, sizeof(format), "%%d\x1F%%d\x1F%%%zu[^\x1E]\x1E%%n",
               buffer_size);
      while (3 ==
             sscanf(ptr, format, &pid_buf, &cmd, buffer, &total_bytes_read)) {
        ptr += total_bytes_read;
        if (MSG == cmd) {  // печатаем только сообщения.
          wprintw(history, "%s: %s\n", pid_to_nick(users, n_users, pid_buf),
                  buffer);
          //    wprintw(history, "%d: %s\n", pid_buf, buffer);
        }
      }  // while sscanf
      free(buffer);
    }
  }  // if (NULL != content)
}
