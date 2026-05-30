#ifndef MQ_CHAT_H
#define MQ_CHAT_H

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

#define CONNECTION_TIMEOUT 60 // в секундах
#define SLEEP_TIME 1 // в секундах
#define SERVER_MQ_NAME "./server.exe"
#define PROJ_ID 1
#define CLIENT_MQ_NAME "./client.exe"
#define MQ_NAME_LENGTH 16
#define MAX_NICKNAME_LENGTH 256
#define COMMAND_LENGTH 6 // ":join " или ":nick " - нужно при извлечении никнейма

struct msgbuf {
    long mtype; //! 1 - сообщения от сервера; (pid_t)2+ - сообщения от клиентов.
    size_t msize;
    char mdata[];
};

enum chat_command {
    JOIN,
    QUIT,
    DISCONNECTED
};

struct chat_msg {
    pid_t sender;
    enum chat_command cmd;
    char *content;
};


unsigned char *allocate_msg_buffer(long *msg_buffer_size);
int clear_mq(char *mq_name);
int connect2mq(char *mq_name, int *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int create_mq(char *mq_name, int *mq_id);
int delete_mq(int mq_id);
void deserialize_msg(const char *mdata, size_t mdata_size, struct chat_msg *msg);
int free_msg_buffer(struct msgbuf **buffer);
int get_last_sender_pid(int mq_id, pid_t *last_sender_pid);
long get_max_msg_size(void);
int get_nickname(char *mtext, char *nickname);
int handle_new_client(struct msgbuf new_client_msg);
int is_mq_empty(int mq_id, long unsigned int *mq_num);
pid_t pid_from_string(unsigned char *string);
unsigned char *pid_to_string(void);
int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg);
int send_mq_msg(int mq_id, struct chat_msg msg);
void serialize_msg(struct chat_msg *msg, size_t content_size, char *mdata);
void *server_queue_handler(void *server_mq_name);
int server_queue_handler_exit(int server_mq_id);
void wait_for_quit(void);

#endif // MQ_CHAT_H
