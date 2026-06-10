#include "client.h"

void close_threads(pthread_t reader_tid, pthread_t sender_tid) {
  int err = 0;
  // проверяем валидность идентификаторов потоков
  int is_reader_tid_valid = 0, is_sender_tid_valid = 0;
  pthread_t main_tid = pthread_self();
  if (0 == pthread_equal(main_tid, reader_tid)) is_reader_tid_valid = 1;
  if (0 == pthread_equal(main_tid, sender_tid)) is_sender_tid_valid = 1;

  if (is_reader_tid_valid && 0 != (err = pthread_cancel(reader_tid))) {
    errno = err;
    perror("reader pthread_cancel");
  }

  if (is_sender_tid_valid && 0 != (err = pthread_cancel(sender_tid))) {
    errno = err;
    perror("sender pthread_cancel");
  }

  if (is_reader_tid_valid) {
    void *reader_return;
    if (0 != (err = pthread_join(reader_tid, &reader_return))) {
      errno = err;
      perror("reader pthread_join");
    } else if (PTHREAD_CANCELED == reader_return) {
      fprintf(stderr, "Инфо: поток чтения сообщений от сервера завершился.\n");
    }
  }

  if (is_sender_tid_valid) {
    void *sender_return;
    if (0 != (err = pthread_join(sender_tid, &sender_return))) {
      errno = err;
      perror("sender pthread_join");
    } else if (PTHREAD_CANCELED == sender_return) {
      fprintf(
          stderr,
          "Инфо: поток для обработки пользовательского ввода завершился.\n");
    }
  }
}
