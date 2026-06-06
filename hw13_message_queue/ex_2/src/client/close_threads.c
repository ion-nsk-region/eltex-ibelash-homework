#include "client.h"

void close_threads(pthread_t reader_tid, pthread_t sender_tid) {
    int err = 0;
    if (0 != (err = pthread_cancel(reader_tid))) {
        errno = err;
        perror("reader pthread_cancel");
    }

    if (0 != (err = pthread_cancel(sender_tid))) {
        errno = err;
        perror("sender pthread_cancel");
    }

    void *reader_return;
    if (0 != (err = pthread_join(reader_tid, &reader_return))) {
        errno = err;
        perror("reader pthread_join");
    } else if (PTHREAD_CANCELED == reader_return) {
        fprintf(stderr, "Инфо: поток чтения сообщений от сервера завершился.\n");
    }

    void *sender_return;
    if (0 != (err = pthread_join(sender_tid, &sender_return))) {
        errno = err;
        perror("sender pthread_join");
    } else if (PTHREAD_CANCELED == sender_return) {
        fprintf(stderr, "Инфо: поток для обработки пользовательского ввода и отправки сообщений завершился.\n");
    }
}
