#include "eltex_shell.h"

int main(void) {
    int err = 0, n_pipes = 2, n_words_total = 6, n_commands;
    char user_input[BUFSIZ] = "ls | grep run | sort";
    char ***arguments = NULL;

    n_commands = parse_multiple_commands(user_input, n_pipes, n_words_total, &arguments);

    if (n_commands == n_pipes + 1) {
        printf("arguments %p\n", arguments);
        for (char ***p = arguments; p - arguments <= n_pipes; p++) {
            printf("Command %p:", *p);
            char **a = *p;
            while (NULL != *a) {
                printf(" %s", *a);
                a++;
            }
            free(*p);
            printf("\n");
        }
        free(arguments);
    } else {
        printf("err = %d\n", err);
    }

    return err;
}
