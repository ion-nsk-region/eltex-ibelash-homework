#include "shm_chat.h"

void detach_shm_segment(void *shm_addr, size_t page_size) {
  errno = 0;
  int err = munmap(shm_addr, page_size);
  if (-1 == err) {
    perror("munmap");
  }
}
