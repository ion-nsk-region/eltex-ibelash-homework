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

#define CONNECTION_TIMEOUT 10  // в секундах
#define SLEEP_TIME 1           // в секундах
#define SERVER_MQ_NAME "./server.exe"
#define PROJ_ID 1
#define CLIENT_MQ_NAME "./client.exe"
#define MQ_NAME_LENGTH 16
#define MAX_NICKNAME_LENGTH 256
#define MAX_PID_STR_LENGTH 12 // размер строки для текстового представления pid
#define MAX_CMD_STR_LENGTH 3 // размер строки для текстового представления номера комманды чата
#define MAX_CHAT_USERS 20
#define MAX_HISTORY_SIZE 100

struct msgbuf {
  long mtype;  //! 1 - сервер; (pid_t)2+ - клиенты.
  size_t msize;
  char mdata[];
};

// при изменении "enum chat_command" также необходимо изменить массив "commands" в server_queue_handler
enum chat_command { NO_COMMAND, //! пустые ячейки истории.
        JOIN, QUIT, LIST, HISTORY, MSG };


struct chat_msg {
  pid_t sender;
  enum chat_command cmd;
  char *content;
};

struct user {
  pid_t pid;
  char *nickname;
};

void cleanup_buffer(void *arg);
int clear_mq(char *mq_name);
int connect2mq(char *mq_name, int *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int create_mq(char *mq_name, int *mq_id);
int delete_mq(int mq_id);
void deserialize_msg(const char *mdata, size_t mdata_size,
                     struct chat_msg *msg);
int get_last_sender_pid(int mq_id, pid_t *last_sender_pid);
long get_max_msg_size(void);
int is_mq_empty(int mq_id, long unsigned int *mq_num);
char *pid_to_nick(struct user *users, int n_users, pid_t pid, int *free_nick);
int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg);
int send_mq_msg(int mq_id, long to_whom, struct chat_msg msg);
void serialize_msg(const struct chat_msg *msg, size_t content_size,
                   char *mdata);

#endif  // MQ_CHAT_H
