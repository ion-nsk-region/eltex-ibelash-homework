#include "server.h"

int server_queue_handler_exit(void *input_shm_addr) {
  int err = 0;
  struct chat_msg msg;
  msg.sender = getpid();
  msg.cmd = QUIT;
  msg.content = NULL;
  msg.msg_size = sizeof(msg.sender) + sizeof(msg.cmd) + sizeof(msg.msg_size);

  errno = 0;
  sem_t *sem4_input_updated = sem_open(SEM4_INPUT_UPDATED, 0);
  if (SEM_FAILED == sem4_input_updated) {
    perror("sem_open");
    err = -1;
  }

  errno = 0;
  sem_t *sem4_input_read = sem_open(SEM4_INPUT_READ, 0);
  if (SEM_FAILED == sem4_input_read) {
    perror("sem_open");
    err = -1;
  }

  if (0 == err) {
    err = send_msg(input_shm_addr, msg, sem4_input_updated, sem4_input_read);
    if (0 != err) {
      printf(
          "Ошибка: не удалось отправить сообщение потоку о выходе. "
          "См. подробности в stderr.\n");
    }
  }

  return err;
}
