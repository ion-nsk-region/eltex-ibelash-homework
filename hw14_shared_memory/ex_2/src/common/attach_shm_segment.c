#include "shm_chat.h"

void *attach_shm_segment(const char *shm_name, size_t shm_size, int shm_flags) {
  void *shm_addr;
  int protection_flags = PROT_READ, perms = 0;
  int err = 0;

  if (O_CREAT == (O_CREAT & shm_flags)) {
    perms = SHM_FD_PERMS;
  }

  errno = 0;
  int shm_fd = shm_open(shm_name, shm_flags, perms);
  if (-1 == shm_fd) {
    perror("shm_open");
    shm_addr = (void *)-1;  // ошибка, когда ничего подчищать не надо
    goto return_shm_addr;
  }

  if (O_CREAT == (O_CREAT & shm_flags)) {
    errno = 0;
    err = ftruncate(shm_fd, (off_t)shm_size);
    if (-1 == err) {
      perror("ftruncate");
      shm_addr = (void *)-2;  // разорвать связь с созданным сегментом
      goto close_shm_fd;
    }
  }

  if (O_RDWR == (O_RDWR & shm_flags)) {
    protection_flags |= PROT_WRITE;
  }
  int memory_flags = MAP_SHARED;
  errno = 0;
  shm_addr = mmap(NULL, shm_size, protection_flags, memory_flags, shm_fd, 0);
  if (MAP_FAILED == shm_addr) {
    perror("mmap");
    shm_addr = (void *)-2; // разорвать связь с сегментом памяти
    goto close_shm_fd;
  }

close_shm_fd:
  errno = 0;
  err = close(shm_fd);
  if (-1 == err) {
    perror("attach_shm_segment > close");
  }

return_shm_addr:
  return shm_addr;
}
