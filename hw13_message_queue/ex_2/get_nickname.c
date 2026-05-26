#include "mq_chat.h"

int get_nickname(char *mtext, char *nickname) {
    int err = 0, nickname_length = 0;
    char *nickname_ptr = nickname, *mtext_ptr = mtext;
    mtext_ptr += COMMAND_LENGTH;

    while('\0' != *mtext_ptr && MAX_NICKNAME_LENGTH > nickname_length) {
        *nickname_ptr = *mtext_ptr;
        mtext_ptr++;
        nickname_ptr++;
        nickname_length++;
    }
    *nickname_ptr = '\0';

    if(2 > nickname_length || MAX_NICKNAME_LENGTH <= nickname_length) {
        fprintf(stderr, "Ошибка: длина ника должна быть от 2 до %d байт. Введено байт: %ld.\n", (MAX_NICKNAME_LENGTH - 1), (strlen(mtext) - COMMAND_LENGTH));
            err = -1;
    }    

    return err;
}
