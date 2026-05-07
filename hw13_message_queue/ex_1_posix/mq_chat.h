#ifndef MQ_CHAT_H
#define MQ_CHAT_H

#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define CONNECTION_TIMEOUT 60 // в секундах
#define SLEEP_TIME 1 // в секундах
#define MSG_LENGTH 255
#define SERVER_MQ_NAME "/posix_server.exe"
#define CLIENT_MQ_NAME "/posix_client.exe"

struct msgbuf {
    long mtype;
    char mtext[MSG_LENGTH];
};

int clear_mq(const char *mq_name);
int connect2mq(char *mq_name, mqd_t *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int create_mq(char *mq_name, mqd_t *mq_id);
int delete_mq(const char *mq_name);
int get_last_sender_pid(mqd_t mq_id, pid_t *last_sender_pid);
int is_mq_empty(mqd_t mq_id, long int *mq_n_messages);
int read_mq_msg(mqd_t mq_id, char **msg);
int send_mq_msg(mqd_t mq_id, const char *msg, size_t msg_length);

#endif // MQ_CHAT_H
