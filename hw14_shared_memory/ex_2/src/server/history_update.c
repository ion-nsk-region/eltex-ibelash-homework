#include <stddef.h>

#include "server.h"

void history_update(struct chat_msg *msg, struct chat_history *history) {
  struct chat_msg *prev_msg = history->last_msg;
  struct chat_msg *new_msg = NULL;

  size_t messages_start = offsetof(struct chat_history, messages);
  size_t messages_end =
      (size_t)sysconf(_SC_PAGESIZE) - offsetof(struct chat_history, messages);
  size_t prev_msg_end = (char *)history->last_msg - (char *)history->messages +
                        history->last_msg->msg_size;

  fprintf(
      stderr,
      "DEBUG: messages_start = %lu, messages_end = %lu, prev_msg_end = %lu\n",
      messages_start, messages_end, prev_msg_end);

  // невпихуемое
  if (prev_msg_end > (messages_end - msg->msg_size)) {
    history->edge_msg = prev_msg;
    new_msg = history->messages;
  } else {
    new_msg = (struct chat_msg *)((char *)prev_msg + prev_msg->msg_size);
  }
  history->last_msg = new_msg;
  size_t new_msg_start = (char *)new_msg - (char *)history->messages;
  size_t new_msg_end = new_msg_start + msg->msg_size;
  size_t first_msg_start =
      (char *)history->first_msg - (char *)history->messages;
  fprintf(
      stderr,
      "DEBUG: new_msg_start = %lu, new_msg_end = %lu, first_msg_start = %lu\n",
      new_msg_start, new_msg_end, first_msg_start);
  unsigned char limit = 0;

  //              |new message|
  //              vvvvvvvvvvvvv
  // last message|     |first message|
  while (new_msg_start <= first_msg_start && new_msg_end >= first_msg_start &&
         255 > limit) {
    struct chat_msg *new_first = NULL;
    if (history->first_msg != history->edge_msg) {
      new_first = (struct chat_msg *)((char *)history->first_msg +
                                      history->first_msg->msg_size);
    } else {
      new_first = history->messages;
    }

    if (is_message(new_first)) {
      history->first_msg = new_first;
      first_msg_start = (char *)history->first_msg - (char *)history->messages;
      fprintf(stderr, "DEBUG: first_msg_start = %lu\n", first_msg_start);
    } else {
      history->first_msg = new_msg;
      break;
    }
    limit++;
  }

  // записываем новое содержимое
  new_msg->msg_size = msg->msg_size;
  new_msg->sender = msg->sender;
  new_msg->cmd = msg->cmd;
  size_t content_length = msg->msg_size - offsetof(struct chat_msg, content);
  strncpy(new_msg->content, msg->content, content_length);
}
