#ifndef CLIENT_H
#define CLIENT_H

#include "mq_chat.h"
#include "client_ui.h"

struct reader_args {
   pthread_mutex_t *refresh_lock; // блокируем цикл main
   pthread_cond_t *refresh_cond;  // пока не прочитаем сообщение от сервера
   struct chat_msg **msg; // сообщение, которое будет обрабатывать main
};

struct input_args {
   pthread_mutex_t *refresh_lock; // --//--
   pthread_cond_t *refresh_cond;  // пока пользователь не введёт что-либо
   int *ch; // введённый символ, который будет обрабатывать main
   // wint_t *ch; // введённый символ, который будет обрабатывать main
};

void close_threads(pthread_t reader_tid, pthread_t input_tid);
void console_handle_msg(struct chat_msg *msg);
void handle_input(WINDOW *msg_input_win, int server_mq_id, int ch, char *input_buf);
int handle_msg(struct chat_msg *msg, struct ui ui);
void *input(void *arg);
void *reader(void *arg);
int spawn_threads(pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond, struct chat_msg **msg, int *ch, pthread_t *reader_tid, pthread_t *input_tid);

#endif // CLIENT_H
