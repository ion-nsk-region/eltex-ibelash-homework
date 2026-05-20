#ifndef MQ_CHAT_H
#define MQ_CHAT_H

#include <errno.h>
#include <fcntl.h>
#include <mqueue.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define CONNECTION_TIMEOUT 60 // в секундах
#define SLEEP_TIME 1 // в секундах
#define SERVER_MQ_NAME "/server.exe"
#define CLIENT_MQ_NAME "/client.exe"

struct mq_msg {
    pid_t sender_pid;
    long int mtext_size;
    char *mtext;
};

enum mq_mode {
    READ = O_RDONLY,
    WRITE = O_WRONLY,
    READ_WRITE = O_RDWR
};

unsigned char *allocate_msg_buffer(mqd_t mq_id, long *msg_buffer_size);
int clear_mq(const char *mq_name);
int connect2mq(char *mq_name, enum mq_mode mq_io_mode, mqd_t *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int create_mq(char *mq_name, enum mq_mode mq_io_mode, mqd_t *mq_id);
int delete_mq(const char *mq_name);
int is_mq_empty(mqd_t mq_id, long int *mq_n_messages);
pid_t pid_from_string(unsigned char *string);
unsigned char *pid_to_string(void);
int read_mq_msg(mqd_t mq_id, char **msg);
int send_mq_msg(mqd_t mq_id, const char *msg, size_t msg_length);
void *server_queue_handler(void *server_mq_name);

#endif // MQ_CHAT_H
