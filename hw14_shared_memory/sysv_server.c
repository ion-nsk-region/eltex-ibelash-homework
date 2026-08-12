#include "shm_chat.h"

int main(void) {
    int err = 0;
    void *shm_addr = NULL;

    char *msg = "Hi!";
    char *reply = NULL;

    err = init_chat(&shm_addr);
    if (0 != err) {
        fprintf(stderr, "Ошибка: не удалось инициализировать чат. Код ошибки: %d\n", err);
    } else {
        send_msg(msg);

        receive_msg(&reply);
        printf("%s\n", reply);

        cleanup(shm_addr);
    }

    return err;
}
