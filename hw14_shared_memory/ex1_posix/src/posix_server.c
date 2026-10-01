#include <unistd.h>

#include "shm_chat.h"

int main(void) {
  int err = 0;
  sem_t *sem4_server, *sem4_client;
  void *shm_addr = NULL;

  err = init_chat(&shm_addr, &sem4_server, &sem4_client);
  if (-1 == err || NULL == shm_addr) {
    fprintf(
        stderr,
        "Ошибка: не удалось инициализировать чат. См. подробности в stderr.\n");
  } else {
    const char *msg = "Hi!";
    char *reply = NULL;

    send_msg(shm_addr, msg);
    notify_msg_sent(sem4_client);
    wait_for_msg(sem4_server);

    receive_msg(shm_addr, &reply);
    printf("%s\n", reply);
    cleanup(shm_addr, sem4_server, sem4_client, reply);
  }

  return err;
}
