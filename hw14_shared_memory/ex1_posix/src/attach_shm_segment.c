#include "shm_chat.h"

void *attach_shm_segment(int shm_fd, size_t shm_size) {
  void *shm_addr;
  int protection_flags = PROT_READ | PROT_WRITE;
  int memory_flags = MAP_SHARED;

  errno = 0;
  shm_addr = mmap(NULL, shm_size, protection_flags, memory_flags, shm_fd, 0);
  if (MAP_FAILED == shm_addr) {
    perror("mmap");
  }

  errno = 0;
  int err = close(shm_fd);
  if (-1 == err) {
    perror("attach_shm_segment > close");
  }

  return shm_addr;
}
