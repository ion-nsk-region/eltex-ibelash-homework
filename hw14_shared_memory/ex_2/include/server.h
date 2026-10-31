#ifndef SERVER_H
#define SERVER_H

#include "common.h"
#include "shm_chat.h"

void *create_and_attach_shm_segment(const char *shm_name, size_t shm_size);
int get_nickname(char *mtext, char *nickname, size_t *nickname_length);
void handle_disconnected_client(pid_t client, struct user *users, int *n_users);
int handle_new_client(struct chat_msg *client_msg, struct user *users,
                      int *n_users);
void history_update(struct chat_msg *msg, struct chat_msg *history);
int init_chat(void **shm_addr, sem_t **sem4_input_updated,
              sem_t **sem4_input_read, struct user **users,
              struct chat_history **history, sem_t **sem4_data_updated,
              sem_t **sem4_count_reads, sem_t **sem4_next_turn);
void notify_about_update(int n_users, sem_t *data_updated, sem_t *count_reads,
                         sem_t *next_turn);
int server_cleanup(void *input_shm_addr, sem_t *input_updated,
                   sem_t *input_read, struct user *users,
                   struct chat_msg *history, sem_t *data_updated,
                   sem_t *count_reads, sem_t *next_turn);
void *server_queue_handler(void *input_shm_addr);
int server_queue_handler_exit(void *input_shm_addr);
int user_add(pid_t pid, const char *nickname, size_t nickname_length,
             struct user *users, int *n_users);
void wait_for_quit(void);

#endif  // SERVER_H
