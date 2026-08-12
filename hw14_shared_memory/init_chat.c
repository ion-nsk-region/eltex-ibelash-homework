#include "shm_chat.h"

int init_chat(void **shm_addr) {
    int err = 0;

    key_t shm_key = ftok(SERVER_FILENAME, PROJ_ID);

    int shm_flags = IPC_CREAT | IPC_EXCL | 0600;
    errno = 0;
    int shm_id = shmget(shm_key, PAGE_SIZE, shm_flags);
    if (-1 == shm_id) {
        err = errno;
        perror("shmget");
        goto exit;
    }

    *shm_addr = shmat(shm_id, NULL, 0);
    if ((void *) -1 == *shm_addr) {
        err = errno;
        perror("shmat");
        goto destroy_shm_segment;
    }



destroy_shm_segment:
    if (-1 == shmctl(shm_id, IPC_RMID, NULL)) {
        err = errno;
        perror("shmctl");
    }

exit:
    return err;
}
