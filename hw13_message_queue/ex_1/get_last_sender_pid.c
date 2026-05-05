#include "mq_chat.h"

int get_last_sender_pid(int mq_id, pid_t *last_sender_pid) {
    int err = 0;
    struct msqid_ds mq_ds;

    errno = 0;
    if (-1 == (err = msgctl(mq_id, IPC_STAT, &mq_ds))) {
        perror("msgctl");
    } else {
        *last_sender_pid = mq_ds.msg_lspid;
    }

    return err;
}
