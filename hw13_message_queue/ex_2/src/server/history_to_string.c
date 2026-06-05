#include "server.h"

int history_to_string(struct chat_msg *history, int *start_msg_id,
                      int last_msg_id, char *buffer, size_t buffer_size) {
  int err = 0;
  size_t bytes_available = buffer_size - 1;

  if (NULL == buffer) {
    fprintf(stderr,
            "Ошибка: history_to_string "
            "не указан адрес результирующей строки.\n");
    err = -1;
  }

  // упаковываем историю сообщений
  if (0 == err) {
    char *buf_ptr = buffer;
    struct chat_msg *msg = history + *start_msg_id;
    const struct chat_msg *end = history + MAX_HISTORY_SIZE;

    while (msg != history + last_msg_id && 0 == err) {
      char pid_str[MAX_PID_STR_LENGTH] = "";
      snprintf(pid_str, MAX_PID_STR_LENGTH, "%d", msg->sender);
      size_t pid_str_length = strlen(pid_str);
      char cmd_str[MAX_CMD_STR_LENGTH] = "";
      snprintf(cmd_str, MAX_CMD_STR_LENGTH, "%d", msg->cmd);
      size_t cmd_str_length = strlen(cmd_str);
      size_t content_length = strlen(msg->content);
      if (bytes_available >
          (pid_str_length + 1 + cmd_str_length + 1 + content_length + 1)) {
        memcpy(buf_ptr, pid_str, pid_str_length);
        buf_ptr += pid_str_length;
        *buf_ptr = 0x1F;  // Unit separator = разделитель полей
        ++buf_ptr;
        memcpy(buf_ptr, cmd_str, cmd_str_length);
        buf_ptr += cmd_str_length;
        *buf_ptr = 0x1F;
        ++buf_ptr;
        memcpy(buf_ptr, msg->content, (content_length));
        buf_ptr = buf_ptr + content_length;
        *buf_ptr = 0x1E;  // Record separator = разделитель записей
        ++buf_ptr;
        bytes_available = bytes_available - (pid_str_length + 1) -
                          (cmd_str_length + 1) - (content_length + 1);
      } else {
        fprintf(
            stderr,
            "Предупреждение: недостаточно места в буфере для всей "
            "истории.\nbytes_avaialble %zu, start %d, current %td, last %d\n",
            bytes_available, *start_msg_id, msg - history, last_msg_id);
        err = ERANGE;
        *start_msg_id =
            msg -
            history;  // возвращаем номер сообщения, на котором мы остановились.
      }

      ++msg;
      if (msg == end) msg = history;  // возвращаемся в начало
    }
    *buf_ptr = '\0';
  }

  return err;
}
