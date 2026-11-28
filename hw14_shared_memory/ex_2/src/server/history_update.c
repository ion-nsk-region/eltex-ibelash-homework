#include <stddef.h>

#include "server.h"

void history_update(const struct chat_msg *msg, struct chat_history *history) {
  size_t prev_msg = history->last_msg;
  size_t new_msg = 0;

  //  size_t messages_start = offsetof(struct chat_history, messages);
  size_t messages_end =
      (size_t)sysconf(_SC_PAGESIZE) - offsetof(struct chat_history, messages);
  /*
    fprintf(
        stderr,
        "DEBUG: messages_start = %lu, messages_end = %lu, prev_msg = %lu\n",
        messages_start, messages_end, prev_msg);
  */
  // проверка впихуемости
  if (prev_msg > (messages_end - msg->msg_size)) {
    history->edge_msg = prev_msg;
    new_msg = 0;
  } else {
    new_msg = prev_msg + get_msg_size(history, prev_msg);
  }
  history->last_msg = new_msg;
  size_t new_msg_end = new_msg + msg->msg_size;
  /* fprintf(
      stderr,
      "DEBUG: new_msg = %lu, new_msg_end = %lu, first_msg = %lu\n",
      new_msg, new_msg_end, history->first_msg);
      */
  unsigned char limit = 0;

  //              |new message|
  //              vvvvvvvvvvvvv
  // last message|     |first message|
  while (new_msg <= history->first_msg && new_msg_end >= history->first_msg &&
         255 > limit) {
    size_t new_first = 0;
    if (history->first_msg != history->edge_msg) {
      new_first =
          history->first_msg + get_msg_size(history, history->first_msg);
    } else {
      new_first = 0;
    }

    if (is_message(history, new_first)) {
      history->first_msg = new_first;
      fprintf(stderr, "DEBUG: first_msg = %zu\n", history->first_msg);
    } else {
      history->first_msg = new_msg;
      break;
    }
    limit++;
  }

  if (255 <= limit) {
    fprintf(stderr,
            "Ошибка: не удалось найти смещение нового начала истории.\n");
    return;
  }

  // записываем новое содержимое
  struct chat_msg *new_msg_ptr =
      (struct chat_msg *)((char *)(history->messages) + new_msg);
  new_msg_ptr->msg_size = msg->msg_size;
  new_msg_ptr->sender = msg->sender;
  new_msg_ptr->cmd = msg->cmd;
  size_t content_length = msg->msg_size - offsetof(struct chat_msg, content);
  strncpy(new_msg_ptr->content, msg->content, content_length);
}
