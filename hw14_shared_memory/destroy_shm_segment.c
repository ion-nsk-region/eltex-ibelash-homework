#include "shm_chat.h"

void destroy_shm_segment(int shm_id) {
    errno = 0;
    if (-1 == shmctl(shm_id, IPC_RMID, NULL)) {
        perror("shmctl");
    }
}
