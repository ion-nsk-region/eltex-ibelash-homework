#include "mq_chat.h"

int main(void) {
  int err = 0;

  char *server_mq_name = SERVER_MQ_NAME;
  char *client_mq_name = CLIENT_MQ_NAME;
  pid_t my_pid = getpid();

  int server_mq_id = -1, client_mq_id = -1;

  // подключаемся к очереди сервера
  err = connect2mq(server_mq_name, &server_mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }
  // подключаемся к очереди для клиентов
  err = connect2mq(client_mq_name, &client_mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  // подключаемся к чату
  if (0 == err && -1 < server_mq_id) {
    struct chat_msg join_msg = {my_pid, JOIN, "Pablo Diego José Francisco "
     "de Paula Juan Nepomuceno María de los Remedios Cipriano de la Santísima "
     "Trinidad Ruiz y Picasso"};
    /* // перегруз по длине никнейма.
     * struct chat_msg join_msg = {
        my_pid, JOIN,
        "Забавно, но моё полное имя Пабло Диего Хосе Франциско де Паула Хуан "
        "Непомучено Мария де лос Ремедиос Чиприано де ла Сантисима Тринидад "
        "Руиз и Пикассо"};
    */

    if (0 != (err = send_mq_msg(server_mq_id, 1, join_msg))) {
      printf("Ошибка send_mq_msg: %d\n", err);
    }
  }
    // считываем сообщение и выводим на экран
    if (0 == err && -1 < client_mq_id) {
      struct chat_msg *reply_from_server;
      if (0 != (err = read_mq_msg(client_mq_id, my_pid, &reply_from_server))) {
        printf("Ошибка read_mq_msg: %d\n", err);
      } else {
        printf("%s\n", reply_from_server->content);
        free(reply_from_server);
      }
    }


  /*
    // отвечаем серверу
    if (0 == err) {
      err = create_mq(client_mq_name, WRITE, &server_mq_id);
    }

    // Удаляем очередь
    if (0 == err && 0 < server_mq_id) {
      long int mq_n_messages = 0;
      int is_empty = 0, n_attempts = 0;
      do {
        is_empty = is_mq_empty(server_mq_id, &mq_n_messages);
      } while (0 == is_empty &&
               ETIME != (err = conn_timer(1, SLEEP_TIME, n_attempts++)));
      if (1 == is_empty) {
        errno = 0;
        if (-1 == (err = mq_close(server_mq_id))) {
          perror("mq_close");
        } else
          server_mq_id = 0;
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
    // printf("Выходим.\n");
    */
  return err;
}
