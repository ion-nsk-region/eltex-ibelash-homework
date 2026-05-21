#include "mq_chat.h"

void deserialize_msg(char *msg_buffer, struct mq_msg *msg) {
    size_t offset = 0;
    memcpy(&msg->sender_pid, msg_buffer + offset, sizeof(pid_t));
    offset += sizeof(pid_t);
    memcpy(&msg->mtext_size, msg_buffer + offset, sizeof(long int));
    offset += sizeof(long int);
    errno = 0;
    msg->mtext = malloc(msg->mtext_size);
    if (NULL == msg->mtext) {
        perror("malloc");
    } else {
        memcpy(msg->mtext, msg_buffer + offset, msg->mtext_size);
        printf("DEBUG msg_buffer %s\nmsg.mtext %s\n%p\n", msg_buffer + offset, msg->mtext, msg->mtext);
    }
}
