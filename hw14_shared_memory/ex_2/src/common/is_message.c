#include "common.h"

int is_message(struct chat_msg *msg) {
  int result = 0;
  if (0 < msg->msg_size) {
    result = 1;
  }
  return result;
}
