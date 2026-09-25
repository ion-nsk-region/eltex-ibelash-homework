#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <errno.h>
#include <unistd.h>  // нам нужна sysconf для получения размера страницы памяти
#include <fcntl.h> // определение констант флагов в shm_open
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/sem.h>
#include <sys/stat.h>

#define SHM_FILENAME "/chat_shm_segment"

// константы для состояний синхронизации через семафор
#define SRV_MSG_SENT 1
#define SRV_WAITING -2
#define CL_MSG_SENT 2
#define CL_WAITING -1

union semun {
  int val;                  // значение для операции SETVAL
  struct semid_ds *buf;     // буфер для операций IPC_STAT и IPC_SET
  unsigned short *array;    // массив для операций GETALL, SETALL
#if defined(__linux__)
  struct seminfo *__buf;    // буфер для операции IPC_INFO (только на Linux)
#endif
};

struct shm_msg {
    size_t msize; 
    char mdata[];
};

void *attach_shm_segment(int shm_fd, size_t shm_size);
void cleanup(int shm_fd, void *shm_addr, int sem4_id, char *reply);
void destroy_semaphore(int sem4_id);
void destroy_shm_segment(const char *shm_name);
void detach_shm_segment(void *shm_addr, size_t page_size);
int init_chat(int *shm_fd, void **shm_addr, int *sem4_id);
int receive_msg(void *shm_addr, char **msg);
int send_msg(void *shm_addr, const char *msg);
void set_state(int sem4_id, int value);

#endif  // SHM_CHAT_H
