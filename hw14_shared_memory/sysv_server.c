#include <unistd.h>
#include "shm_chat.h"

int main(void) {
    int err = 0, shm_id, sem4_id;
    void *shm_addr = NULL;

/*
    char *msg = "Hi!";
    char *reply = NULL;
*/

    err = init_chat(&shm_id, &shm_addr, &sem4_id);
    if (-1 == err || NULL == shm_addr) {
        fprintf(stderr, "Ошибка: не удалось инициализировать чат. См. подробности в stderr.\n");
    } else {
            /*
        send_msg(shm_addr, msg);

        receive_msg(shm_addr, &reply);
        printf("%s\n", reply);
        */
            sleep(10);
        cleanup(shm_id, shm_addr, sem4_id);
    }

    return err;
}
