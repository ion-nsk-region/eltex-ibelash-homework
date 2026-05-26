#include "mq_chat.h"

int get_nickname(char *mtext, char *nickname) {
    int err = 0, nickname_length = 0;
    char *nickname_ptr = nickname, *mtext_ptr = mtext;
    mtext_ptr += strlen(":join ");

    while('\0' != *mtext_ptr && MAX_NICKNAME_LENGTH > nickname_length) {
        *nickname_ptr = *mtext_ptr;
        mtext_ptr++;
        nickname_ptr++;
        nickname_length++;
    }

    if(2 > nickname_length || MAX_NICKNAME_LENGTH <= nickname_length) {
        fprintf(stderr, "Ошибка: длина ника должна быть от 2 до %d байт. Передано %d байт.\n", MAX_NICKNAME_LENGTH, nickname_length);
            err = -1;
    }    

    return err;
}
