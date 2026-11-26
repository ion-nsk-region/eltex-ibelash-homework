#include <stdint.h>
#include "client.h"

int close_input_thread(pthread_t input_tid) {
  int err = 0;
  // проверяем валидность идентификатора потока
  pthread_t main_tid = pthread_self();
  err = pthread_equal(main_tid, input_tid);
  if (0 != err) {
    fprintf(stderr,
            "Предупреждение: поток обработки ввода не был запущен. "
            "См. предыдущие сообщения для выяснения причины.\n");
    return -1;
  }

  err = pthread_cancel(input_tid);
  if (0 != err) {
    errno = err;
    perror("input pthread_cancel");
  }

  void *input_return;
  err = pthread_join(input_tid, &input_return);
  if (0 != err) {
    errno = err;
    perror("input pthread_join");
  } else if (PTHREAD_CANCELED == input_return || (void *)0 == input_return) {
    fprintf(stderr, "Инфо: поток обработки ввода завершился.\n");
  } else {
    fprintf(stderr, "Предупреждение: поток обработки ввода завершился с неожиданным результатом: %ld.\n", (intptr_t)input_return);
  }

  return err;
}
