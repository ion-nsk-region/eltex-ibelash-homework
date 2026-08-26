#include "shm_chat.h"

void set_state(int sem4_id, int value) {
  struct sembuf sop;

  sop.sem_num = 0;
  sop.sem_op = value;
  sop.sem_flg = 0;

  int err = semop(sem4_id, &sop, 1);
  if (-1 == err) {
    perror("semop");
  }
}
