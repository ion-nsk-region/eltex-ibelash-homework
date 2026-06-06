#include "client.h"

int spawn_threads(pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond, struct chat_msg **msg, int *ch, pthread_t *reader_tid, pthread_t *sender_tid) {
  int err = 0;
  pthread_mutex_init(refresh_lock, NULL);
  pthread_cond_init(refresh_cond, NULL);

  // запускаем поток для чтения сообщений от сервера
  struct reader_args reader_args;
  reader_args.refresh_lock = refresh_lock;
  reader_args.refresh_cond = refresh_cond;
  reader_args.msg = msg;

  if (0 != (err = pthread_create(reader_tid, NULL, reader, &reader_args))) {
    perror("reader pthread_create");
  }
  
  // запускаем поток для обработки пользовательского ввода и отправки сообщений
  if (0 == err) {
    struct sender_args sender_args;
    sender_args.refresh_lock = refresh_lock;
    sender_args.refresh_cond = refresh_cond;
    sender_args.ch = ch;
    if (NULL != sender_args.ch && NULL != sender_tid) {;}

//    if (0 != (err = pthread_create(sender_tid, NULL, sender, &sender_args))) {
//      perror("sender pthread_create");
//    }
  }

  return err;
}
