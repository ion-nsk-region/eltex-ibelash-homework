#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *server_mq_name = SERVER_MQ_NAME;
  mqd_t mq_id = 0;
  pthread_t server_queue_handler_tid;

  // очередь для чтения входящих сообщений от клиентов
  if (0 != (err = create_mq(server_mq_name, READ_WRITE, &mq_id))) {
    fprintf(stderr, "Ошибка: не удалось создать очередь сообщений для обработки"
                    "сообщений от клиентов. См. подробности в stderr.\n");
  }

  // создаём поток для обработки сообщений от клиентов
  if(0 != (err = pthread_create(&server_queue_handler_tid, NULL, server_queue_handler, server_mq_name))) {
    fprintf(stderr, "Ошибка: не удалось создать поток для обработки входящих сообщений от клиентов:\n%s\n", strerror(err));
  }
  
  // завершаем работу при нажатии "q"
  do {
    printf("Нажмите 'q' для завершения работы сервера.\n");
  } while ('q' != getchar());

  // отправляем сообщение потоку о выходе
  long msg_buffer_size = 0;
  char *msg_buffer = (char *)allocate_msg_buffer(mq_id, &msg_buffer_size);
  if (NULL != msg_buffer) {
  struct mq_msg msg;
  msg.sender_pid = getpid();
  msg.mtext_size = sizeof("/quit");
  msg.mtext = "/quit";
  long msg_size = sizeof(pid_t) + sizeof(long int) + msg.mtext_size;
  if (msg_size > msg_buffer_size) {
    fprintf(stderr, "Ошибка: размер отправляемого сообщения больше размера буфера очереди сообщений. Необходимо настроить очередь сообщений для приёма сообщений большего размера.\n");
    err = -1;
  } else {
    size_t offset = 0;
    memcpy(msg_buffer + offset, &msg.sender_pid, sizeof(pid_t));
    offset += sizeof(pid_t);
    memcpy(msg_buffer + offset, &msg.mtext_size, sizeof(long int));
    offset += sizeof(long int);
    memcpy(msg_buffer + offset, &msg.mtext, msg.mtext_size);
    err = send_mq_msg(mq_id, msg_buffer, msg_buffer_size);
  }
  }

  void *status;
  if(0 == (err = pthread_join(server_queue_handler_tid, &status))) {
    long int exit_code = (long int)status;
    if (0 != exit_code) {
        printf("Поток обработки входящих сообщений от клиентов завершился со статусом %ld\n", exit_code);
    }
  } else {
    fprintf(stderr, "pthread_join: %s\n", strerror(err));
  }

  // очищаем выделенные ресурсы
  /*
  if (0 == err) {
    server_cleanup(); 
  }
*/

  // Выходим
  //  printf("Выходим.\n");

  return err;
}
