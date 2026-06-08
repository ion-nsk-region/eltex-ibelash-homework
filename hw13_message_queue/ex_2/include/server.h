#ifndef SERVER_H
#define SERVER_H

#include "mq_chat.h"

int get_nickname(char *mtext, char *nickname, size_t *nickname_length);
int handle_new_client(int client_mq_id, struct chat_msg client_msg, struct user *users, int *n_users, struct chat_msg *history, int last_msg_id);
int history_send(int client_mq_id, long to_whom,
                  struct chat_msg *history, int last_msg_id);
int history_to_string(struct chat_msg *history, int *start_msg_id, int last_msg_id, char *buffer, size_t buffer_size);
void history_update(struct chat_msg msg, struct chat_msg *history, int *last_msg_id);
int msg_to_all(int client_mq_id, struct chat_msg msg, struct user *users,
                int n_users);
int send_user_joined_notification(int client_mq_id, struct user *users, int n_users, const char *client_nickname, size_t client_nickname_length);
int send_users_list(int client_mq_id, struct user *users, int n_users);
int server_cleanup(int server_mq_id, int client_mq_id, struct user *users, int n_users, struct chat_msg *history);
void *server_queue_handler(void *server_mq_name);
int server_queue_handler_exit(int server_mq_id);
int user_add(pid_t pid, const char *nickname, size_t nickname_length,
             struct user *users, int *n_users);
int users_list_to_string(struct user *users, int n_users, char *buffer,
                         size_t buffer_size);
void wait_for_quit(void);

#endif // SERVER_H
