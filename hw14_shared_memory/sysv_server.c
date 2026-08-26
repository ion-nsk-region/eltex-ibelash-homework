#include <unistd.h>

#include "shm_chat.h"

int main(void) {
  int err = 0, shm_id, sem4_id;
  void *shm_addr = NULL;

  err = init_chat(&shm_id, &shm_addr, &sem4_id);
  if (-1 == err || NULL == shm_addr) {
    fprintf(
        stderr,
        "Ошибка: не удалось инициализировать чат. См. подробности в stderr.\n");
  } else {
    const char *msg = "Hi!";
    char *reply = NULL;

    send_msg(shm_addr, msg);
    set_state(sem4_id, SRV_MSG_SENT);
    set_state(sem4_id, SRV_WAITING);

    receive_msg(shm_addr, &reply);
    printf("%s\n", reply);
    //    sleep(10);
    cleanup(shm_id, shm_addr, sem4_id, reply);
  }

  return err;
}
