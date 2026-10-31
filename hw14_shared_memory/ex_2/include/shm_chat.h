#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <errno.h>
#include <fcntl.h> // для константы O_CREAT
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h> // mmap, PROT_READ, PROT_WRITE
#include <sys/stat.h> // для констант режима доступа
#include <unistd.h> // close

#define MAX_NICKNAME_LENGTH 256
#define MAX_PID_STR_LENGTH 12 // размер строки для текстового представления pid
#define MAX_CMD_STR_LENGTH 3 // размер строки для текстового представления номера комманды чата
#define MAX_CHAT_USERS 20
#define MAX_HISTORY_SIZE 100

#define SHM_INPUT "/shm_input"
#define SHM_HISTORY "/shm_history"
#define SHM_USERS "/shm_users"
#define SEM4_INPUT_UPDATED "/sem4_input_updated"
#define SEM4_INPUT_READ "/sem4_input_read"
#define SEM4_DATA_UPDATED "/sem4_data_updated"
#define SEM4_COUNT_READS "/sem4_count_reads"
#define SEM4_NEXT_TURN "/sem4_next_turn"

enum chat_command { NO_COMMAND, //! пустые ячейки истории
                                JOIN, QUIT, LIST, HISTORY, MSG };

struct chat_msg {
    size_t msg_size;
    pid_t sender;
    enum chat_command cmd;
    char *content;
};

struct user {
    pid_t pid;
    char nickname[MAX_NICKNAME_LENGTH]; // в отличие от предыдущей реализации, память уже выделена.
};

struct chat_history {
	void *first_msg;
	void *last_msg;
	void *edge_msg; // крайнее сообщение на границе выделенной памяти, 
			// после которого прыгаем в начало сегмента памяти
	struct chat_msg *messages;
}

#endif // SHM_CHAT_H
