#ifndef SHM_CHAT_H
#define SHM_CHAT_H

enum chat_command { NO_COMMAND, //! пустые ячейки истории
                                JOIN, QUIT, LIST, HISTORY, MSG };

struct chat_msg {
    size_t msg_size;
    pid_t sender;
    enum chat_command cmd;
    char *content;
}

struct user {
    pid_t pid;
    char *nickname;
}

#endif // SHM_CHAT_H
