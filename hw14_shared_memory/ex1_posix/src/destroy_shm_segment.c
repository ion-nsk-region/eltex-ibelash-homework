#include "shm_chat.h"

void destroy_shm_segment(const char *shm_name) {
  errno = 0;
  if (-1 == shm_unlink(shm_name)) {
    perror("shm_unlink");
  }
}
