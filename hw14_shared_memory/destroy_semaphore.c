#include "shm_chat.h"

void destroy_semaphore(int sem4_id) {
    union semun dummy;
    errno = 0;
    int err = semctl(sem4_id, 0, IPC_RMID, dummy);
    if (-1 == err) {
        perror("destroy_semaphore > semctl");
    }
}
