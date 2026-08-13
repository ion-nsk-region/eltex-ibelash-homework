#include "shm_chat.h"

void *attach_shm_segment(int shm_id) {
    void *shm_addr;

    errno = 0;
    shm_addr = shmat(shm_id, NULL, 0);
    if ((void *) -1 == shm_addr) {
        perror("shmat");
    }

    return shm_addr;
}
