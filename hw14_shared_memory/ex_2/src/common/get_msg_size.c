#include "shm_chat.h"

size_t get_msg_size(struct chat_history *history, size_t msg_offset) {
  size_t msg_size =
      ((struct chat_msg *)((char *)(history->messages) + msg_offset))->msg_size;

  return msg_size;
}
