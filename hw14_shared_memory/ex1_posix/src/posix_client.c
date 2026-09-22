#include <stdlib.h>

#include "shm_chat.h"

int main(void) {
  int err = 0, shm_id, sem4_id;
  void *shm_addr = NULL;

  key_t key = ftok(SERVER_FILENAME, PROJ_ID);
  errno = 0;
  shm_id = shmget(key, 1, 0);
  if (-1 == shm_id) {
    perror("shmget");
    err = -1;
    goto exit;
  }

  shm_addr = attach_shm_segment(shm_id);
  if ((void *)-1 == shm_addr) {
    fprintf(stderr,
            "Ошибка: не удалось подключить сегмент разделяемой памяти. "
            "Проверьте, что сервер запущен.\n");
    err = -2;
    goto exit;
  }

  errno = 0;
  sem4_id = semget(key, 1, 0);
  if (-1 == sem4_id) {
    perror("semget");
    err = -3;
    goto exit;
  }

  char *msg = NULL;
  set_state(sem4_id, CL_WAITING);
  receive_msg(shm_addr, &msg);
  printf("%s\n", msg);
  free(msg);

  const char *reply = "Hello!";
  send_msg(shm_addr, reply);
  set_state(sem4_id, CL_MSG_SENT);

exit:

  return err;
}
