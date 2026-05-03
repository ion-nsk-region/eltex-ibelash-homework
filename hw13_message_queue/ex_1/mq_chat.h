#ifndef MQ_CHAT_H
#define MQ_CHAT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define PROJ_ID 1
#define CONNECTION_TIMEOUT 60 // в секундах
#define SLEEP_TIME 1 // в секундах
#define MSG_LENGTH 255

struct msgbuf {
    long mtype;
    char mtext[MSG_LENGTH];
};

int connect2mq(char *mq_name, int mq_flags, int *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int read_mq_msg(int mq_id, long msg_type, char *msg);
int send_mq_msg(int mq_id, char *msg, size_t msg_length);

#endif // MQ_CHAT_H
