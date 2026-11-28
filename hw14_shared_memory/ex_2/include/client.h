#ifndef CLIENT_H
#define CLIENT_H

#include "client_ui.h"
#include "common.h"
#include "shm_chat.h"

struct input_args {
   struct chat_msg *msg; ///< разделяемая память для отправки сообщений на сервер
   sem_t *input_updated; ///< уведомление серверу о новом сообщении
   sem_t *input_read;    ///< уведомление от сервера о готовности принимать данные
   WINDOW *input_window; ///< поле ввода сообщения в интерфейсе клиента
};

void client_cleanup(struct chat_msg **msg, sem_t **input_updated,
                   sem_t **input_read, struct user **users,
                   struct chat_history **history, sem_t **data_updated,
                   sem_t **count_reads, sem_t **next_turn, const struct ui *ui);
int close_input_thread(pthread_t input_tid);
void console_handle_msg(struct chat_msg *msg);
void handle_input(struct ui ui, int server_mq_id, int ch, char *input_buf, size_t *input_buf_length);
int handle_msg(struct chat_msg *msg, struct ui ui, struct user *users, int *n_users);
int init_client(struct chat_msg **msg, sem_t **input_updated,
                sem_t **input_read, struct user **users,
                struct chat_history **history, sem_t **data_updated,
                sem_t **count_reads, sem_t **next_turn, struct ui *ui);
int join_chat(struct chat_msg *input, sem_t *input_updated, sem_t *input_read);
void *input(void *arg);
int nickname_prompt(char *nickname, size_t *nickname_length);
void on_key_backspace(WINDOW *input, char *input_buf, size_t *input_buf_length);
void on_key_enter(struct chat_msg *input, sem_t *input_updated, sem_t *input_read, WINDOW *input_window, char *input_buf, size_t *input_buf_length);
int spawn_input_thread(struct chat_msg *msg, sem_t *input_updated, sem_t *input_read, WINDOW *input_window, pthread_t *input_tid);

#endif // CLIENT_H
