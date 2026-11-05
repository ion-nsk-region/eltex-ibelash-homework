#include <stddef.h>

#include "server.h"

void history_update(struct chat_msg *msg, struct chat_history *history) {
  struct chat_msg *prev_msg = history->last_msg;
  struct chat_msg *new_msg = NULL;
  size_t page_size = (size_t)sysconf(_SC_PAGESIZE);
  void *history_end = history + page_size;
  // невпихуемое
  if ((void *)(prev_msg + prev_msg->msg_size) > (history_end - msg->msg_size)) {
    history->edge_msg = prev_msg;
    new_msg = history->messages;
  } else {
    new_msg = prev_msg + prev_msg->msg_size;
  }
  history->last_msg = new_msg;

  //              |new message|
  //              vvvvvvvvvvvvv
  // last message|     |first message|
  while (new_msg <= history->first_msg &&
         (new_msg + msg->msg_size) >= history->first_msg) {
    void *new_start = NULL;
    if (history->first_msg != history->edge_msg) {
      new_start = history->first_msg + history->first_msg->msg_size;
    } else {
      new_start = history->messages;
    }
    history->first_msg = new_start;
  }

  // записываем новое содержимое
  new_msg->msg_size = msg->msg_size;
  new_msg->sender = msg->sender;
  new_msg->cmd = msg->cmd;
  size_t content_length = msg->msg_size - offsetof(struct chat_msg, content);
  strncpy(new_msg->content, msg->content, content_length);
}
