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
    struct chat_msg join_msg = {my_pid, JOIN,
                                "Pablo Diego José Francisco "
                                "de Paula Juan Nepomuceno María de los "
                                "Remedios Cipriano de la Santísima "
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

  // заполняем историю
  if (0 == err && -1 < client_mq_id) {
    struct chat_msg some_msg = {my_pid, MSG, NULL};
    some_msg.content = malloc(280);
    for (int i = 0; i < 10; ++i) {
      sprintf(some_msg.content,
              "Это очень длинное сообщение номер %d. Сейчас мы попытаемся "
              "забить буфер так, чтобы серверу приходилось отправлять по два "
              "сообщения из истории.",
              i);
      if (0 != (err = send_mq_msg(server_mq_id, 1, some_msg))) {
        printf("Ошибка send_mq_msg: %d\n", err);
      }
      usleep(100);
    }
    if (NULL != some_msg.content) {
      free(some_msg.content);
    }
  }

  // считываем сообщения от сервера и выводим на экран
  if (0 == err && -1 < client_mq_id) {
    for (int i = 0; i < 25; ++i) {
      struct chat_msg *reply_from_server;
      if (0 != (err = read_mq_msg(client_mq_id, my_pid, &reply_from_server))) {
        printf("Ошибка read_mq_msg: %d\n", err);
      } else {
        const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                                  "LIST",       "HISTORY", "MSG"};
        printf("\n\nПолучено сообщение типа %s: %s\n",
               commands[reply_from_server->cmd], reply_from_server->content);
        free(reply_from_server->content);
        free(reply_from_server);
      }
    }
  }

  return err;
}
