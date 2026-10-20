#include "server.h"

int main(void) {
  int err = 0;
  pthread_t server_queue_handler_tid;
  void *shm_msg_addr = NULL;

  // создаём поток для обработки сообщений от клиентов
  err = pthread_create(&server_queue_handler_tid, NULL, server_queue_handler,
                       &shm_msg_addr);
  if (0 != err) {
    fprintf(stderr,
            "Ошибка: не удалось создать поток для обработки входящих сообщений "
            "от клиентов:\n%s\n",
            strerror(err));
  }

  if (0 == err) {
    // завершаем работу при нажатии "q"
    wait_for_quit();

    // отправляем сообщение потоку о выходе
    server_queue_handler_exit(shm_msg_addr);

    void *status;
    err = pthread_join(server_queue_handler_tid, &status);
    if (0 == err) {
      int exit_code = (int)(intptr_t)status;
      if (0 != exit_code) {
        printf(
            "Поток обработки входящих сообщений от клиентов завершился со "
            "статусом %d\n",
            exit_code);
      }
    } else {
      fprintf(stderr, "pthread_join: %s\n", strerror(err));
    }
  }

  return err;
}
