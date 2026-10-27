#include "shm_chat.h"

void *create_and_attach_shm_segment(const char *shm_name, size_t shm_size) {
  void *shm_addr;
  int perms = 0600;
  int flags = O_CREAT | O_RDWR;

  // input
  errno = 0;
  int shm_fd = shm_open(shm_name, flags, perms);
  if (-1 == shm_fd) {
    perror("shm_open");
    return (void *)-1;
  }

  errno = 0;
  if (-1 == ftruncate(shm_fd, (off_t)shm_size)) {
    perror("ftruncate");
    return (void *)-2; // destroy_shm
  }

  shm_addr = attach_shm_segment(shm_fd, shm_size);
  if (MAP_FAILED == *shm_addr) {
    return (void *)-2; // destroy_shm
  }

  return shm_addr;
}
