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

#define CONNECTION_TIMEOUT 60  // в секундах
#define SLEEP_TIME 1           // в секундах
#define SERVER_MQ_NAME "./server.exe"
#define PROJ_ID 1
#define CLIENT_MQ_NAME "./client.exe"
#define MQ_NAME_LENGTH 16
#define MAX_NICKNAME_LENGTH 256
#define MAX_CHAT_USERS 20
#define MAX_HISTORY_SIZE 100

struct msgbuf {
  long mtype;  //! 1 - сообщения от сервера; (pid_t)2+ - сообщения от клиентов.
  size_t msize;
  char mdata[];
};

enum chat_command { JOIN, QUIT, LIST, DISCONNECTED, MSG };

const char *commands[] = {"JOIN", "QUIT", "LIST", "DISCONNECTED", "MSG" };

struct chat_msg {
  pid_t sender;
  enum chat_command cmd;
  char *content;
};

struct user {
  pid_t pid;
  char *nickname;
};

int clear_mq(char *mq_name);
int connect2mq(char *mq_name, int *mq_id);
int conn_timer(int connection_timeout, int sleep_time, int n_attempts);
int create_mq(char *mq_name, int *mq_id);
int delete_mq(int mq_id);
void deserialize_msg(const char *mdata, size_t mdata_size,
                     struct chat_msg *msg);
int get_last_sender_pid(int mq_id, pid_t *last_sender_pid);
long get_max_msg_size(void);
int get_nickname(char *mtext, char *nickname, size_t *nickname_length);
int handle_new_client(int client_mq_id, struct chat_msg client_msg, struct user *users, int *n_users, struct chat_msg *history, char last_msg_id);
int is_mq_empty(int mq_id, long unsigned int *mq_num);
pid_t pid_from_string(unsigned char *string);
unsigned char *pid_to_string(void);
int read_mq_msg(int mq_id, long msg_type, struct chat_msg **msg);
int send_mq_msg(int mq_id, long to_whom, struct chat_msg msg);
int send_users_list(int client_mq_id, long to_whom, struct user *users,
                    int n_users);
void serialize_msg(const struct chat_msg *msg, size_t content_size,
                   char *mdata);
int server_cleanup(int server_mq_id, int client_mq_id);
void *server_queue_handler(void *server_mq_name);
int server_queue_handler_exit(int server_mq_id);
int user_add(pid_t pid, char *nickname, size_t nickname_length,
             struct user *users, int *n_users);
int users_list_to_string(struct user *users, int n_users,
                         size_t max_buffer_size, char *buffer);
void wait_for_quit(void);

#endif  // MQ_CHAT_H
