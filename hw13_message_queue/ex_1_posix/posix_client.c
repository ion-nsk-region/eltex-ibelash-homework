#include "mq_chat.h"

int main(void) {
  int err = 0;

  char *server_mq_name = SERVER_MQ_NAME;
  char *client_mq_name = CLIENT_MQ_NAME;
  char *msg = NULL;
  char *reply = "Hello!";

  mqd_t mq_id = 0;

  // подключаемся к очереди
  err = connect2mq(server_mq_name, &mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  // считываем сообщение и выводим на экран
  if (0 == err && 0 != mq_id) {
    if (0 != (err = read_mq_msg(mq_id, &msg))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    } else {
      printf("%s\n", msg);
      free(msg);
    }
  }

  // отключаемся от очереди сервера
  if (0 == err && 0 != mq_id) {
    errno = 0;
    if (-1 == (err = mq_close(mq_id))) {
      perror("mq_close");
    }
  }

  // отвечаем серверу
  if (0 == err) {
    err = create_mq(client_mq_name, &mq_id);
  }
  if (0 == err && 0 != mq_id &&
      (0 != (err = send_mq_msg(mq_id, reply, sizeof(reply))))) {
    printf("Ошибка send_mq_msg: %d\n", err);
  }

  // Удаляем очередь
  if (0 == err) {
    long int mq_n_messages = 0;
    int is_empty = 0, n_attempts = 0;
    do {
      is_empty = is_mq_empty(mq_id, &mq_n_messages);
    } while (0 == is_empty &&
             ETIME != (err = conn_timer(1, SLEEP_TIME, n_attempts++)));
    if (1 == is_empty) {
      errno = 0;
      if (-1 == (err = mq_close(mq_id))) {
        perror("mq_close");
      }
      if (0 == err && 0 != (err = delete_mq(client_mq_name))) {
        printf(
            "Ошибка: не удалось удалить очередь сообщений.\n"
            "См. подробности в stderr.\n"
            "Перезагрузите компьютер для удаления вручную.\n");
      }
    } else if (0 == is_empty) {
      printf(
          "Предупреждение: Очередь не была удалена.\n"
          "Она не пуста и содержит %ld сообщений.\n"
          "Перезагрузите компьютер для удаления вручную.\n",
          mq_n_messages);
    } else {
      printf(
          "Ошибка: Не удалось проверить состояние очереди.\n"
          "См. подробности в stderr.\n");
    }
  }

  // выходим
  printf("Выходим.\n");
  return err;
}
