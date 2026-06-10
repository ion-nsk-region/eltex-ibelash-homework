#ifndef CLIENT_H
#define CLIENT_H

#include "mq_chat.h"
#include "client_ui.h"

struct reader_args {
   pthread_mutex_t *refresh_lock; // блокируем цикл main
   pthread_cond_t *refresh_cond;  // пока не прочитаем сообщение от сервера
   pthread_mutex_t *processing_lock; // затем блокируем поток 
   pthread_cond_t *processing_cond;  // на время обработки сообщения
   struct chat_msg **msg; // сообщение, которое будет обрабатывать main
   int *is_processing;   // флаг, сообщающий что main обрабатывает сообщение
};

struct input_args {
   pthread_mutex_t *refresh_lock; // --//--
   pthread_cond_t *refresh_cond;  // пока пользователь не введёт что-либо
   pthread_mutex_t *processing_lock; // затем блокируем поток 
   pthread_cond_t *processing_cond;  // на время обработки введённого символа
   int *ch; // введённый символ, который будет обрабатывать main
   int *is_processing;   // флаг, сообщающий что main обрабатывает символ
   WINDOW *input_window; 
   // wint_t *ch; // введённый символ, который будет обрабатывать main
//   WINDOW *win; // требовался, чтобы обрабатывать изменение размера...но ну его.
};

void client_cleanup(pthread_t reader_tid, pthread_t input_tid,
                    pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond,
                    pthread_mutex_t *msg_processing_lock,
                    pthread_cond_t *msg_processing_cond,
                    pthread_mutex_t *ch_processing_lock,
                    pthread_cond_t *ch_processing_cond, struct user *users,
                    int n_users);
void close_threads(pthread_t reader_tid, pthread_t input_tid);
void console_handle_msg(struct chat_msg *msg);
void handle_input(struct ui ui, int server_mq_id, int ch, char *input_buf, size_t *input_buf_length);
int handle_msg(struct chat_msg *msg, struct ui ui, struct user *users, int *n_users);
void *input(void *arg);
int nickname_prompt(int server_mq_id);
void on_key_backspace(struct ui ui, char *input_buf, size_t *input_buf_length);
void on_key_enter(struct ui ui, int server_mq_id, char *input_buf,
                  size_t *input_buf_length);
void *reader(void *arg);
int spawn_threads(pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond,
                  struct chat_msg **msg, int *msg_is_processing,
                  pthread_mutex_t *msg_processing_lock,
                  pthread_cond_t *msg_processing_cond, int *ch,
                  int *ch_is_processing, pthread_mutex_t *ch_processing_lock,
                  pthread_cond_t *ch_processing_cond, WINDOW *input_window, 
                  pthread_t *reader_tid, pthread_t *input_tid);

#endif // CLIENT_H
