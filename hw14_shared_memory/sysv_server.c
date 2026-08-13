#include "shm_chat.h"

int main(void) {
    int err = 0;
    void *shm_addr = NULL;

    char *msg = "Hi!";
    char *reply = NULL;

    shm_addr = init_chat();
    if (NULL == shm_addr) {
        fprintf(stderr, "Ошибка: не удалось инициализировать чат. См. подробности в stderr.\n");
    } else {
        send_msg(msg);

        receive_msg(&reply);
        printf("%s\n", reply);

        cleanup(shm_addr);
    }

    return err;
}
