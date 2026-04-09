#include "ex_1.h"

int main(void) {
    int err = 0;
    int my_pipe[2];
    char msg[BUFSIZ];

    err = create_pipe(my_pipe);
    if (0 > err) {
        printf("Ошибка: не удалость создать канал для передачи сообщения.\n"
               "Код ошибки: %d. См. подробности в stderr.\nВыходим.\n", err);
        return err;
    }
    errno = 0;
    pid_t child_pid = fork();
    if (-1 == child_pid) {
        perror("fork");
        err -= 1;
    } else if(0 < child_pid) {
        if (0 == close_pipe(my_pipe[0])) { // закрываем на чтение
            send_msg_to_pipe(my_pipe, "Hi!");
            err = wait4child(child_pid);
        }
    } else if (0 == child_pid) {
        if (0 == close_pipe(my_pipe[1])) { // закрываем на запись
            read_msg_from_pipe(my_pipe, msg);
            printf("%s", msg);
        }
    }

    return err;
}
