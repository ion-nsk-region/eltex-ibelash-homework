#include "common.h"

int is_message(struct chat_history *history, size_t msg_offset) {
  int result = 0;
  if (0 < get_msg_size(history, msg_offset)) {
    result = 1;
  }
  return result;
}
