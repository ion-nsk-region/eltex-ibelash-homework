#include "shm_chat.h"

void detach_shm_segment(void *shm_addr) {
    errno = 0;
    int err = shmdt(shm_addr);
    if (-1 == err) {
        perror("shmdt");
    }
}
