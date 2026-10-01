#include <stdlib.h>

#include "shm_chat.h"

int main(void) {
  int err = 0;
  sem_t sem4_server, sem4_client;
  void *shm_addr = NULL;

  err = init_client(&shm_addr, &sem4_server, &sem4_client);
  if (-1 == err) {
    fprintf(stderr,
            "Ошибка: не удалось инициализировать клиента. "
            "См. подробности в stderr.\n");
  } else {
    char *msg = NULL;
    wait_for_msg(&sem4_client);
    receive_msg(shm_addr, &msg);
    printf("%s\n", msg);
    free(msg);

    const char *reply = "Hello!";
    send_msg(shm_addr, reply);
    notify_msg_sent(&sem4_server);
  }

  return err;
}
