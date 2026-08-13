#include "shm_chat.h"

void *init_chat(void) {

    key_t key = ftok(SERVER_FILENAME, PROJ_ID);
    int flags = IPC_CREAT | IPC_EXCL | 0600;

    errno = 0;
    int shm_id = shmget(key, PAGE_SIZE, flags);
    if (-1 == shm_id && EEXIST != errno) {
        perror("shmget");
        goto err_exit;
    }

    void shm_addr = attach_shm_segment(shm_id);
    if ((void *) -1 == shm_addr) {
        goto destroy_shm_segment;
    }

    errno = 0;
    int sm4_id = semget(key, 1, flags);
    if (-1 == sm4_id && EEXIST != errno) {
        perror("semget");
        goto detach_shm_segment;
    }

    return shm_addr;

detach_shm_segment:
    detach_shm_segment(shm_addr);

destroy_shm_segment:
    destroy_shm_segment(shm_id);

err_exit:
    return NULL;
}
