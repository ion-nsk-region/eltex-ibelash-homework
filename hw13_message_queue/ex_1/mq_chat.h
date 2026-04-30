#ifndef MQ_CHAT_H
#define MQ_CHAT_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define PROJ_ID 1
#define CONNECTION_TIMEOUT 60 // в секундах
#define SLEEP_TIME 1 // в секундах

int connect2mq(char *mq_name, int *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);

#endif // MQ_CHAT_H
