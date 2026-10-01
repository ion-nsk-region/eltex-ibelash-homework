#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <errno.h>
#include <unistd.h>  // нам нужна sysconf для получения размера страницы памяти
#include <fcntl.h> // определение констант флагов в shm_open
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHM_FILENAME "/chat_shm_segment"
#define SEM4_SERVER "/chat_sem4_server"
#define SEM4_CLIENT "/chat_sem4_client"

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
void cleanup(void *shm_addr, sem_t *sem4_server, sem_t *sem4_client, char *reply);
int close_semaphore(sem_t *sem4_id);
void destroy_semaphore(sem_t *sem4_id, const char *sem4_name);
void destroy_shm_segment(const char *shm_name);
void detach_shm_segment(void *shm_addr, size_t page_size);
int init_chat(void **shm_addr, sem_t *sem4_server, sem_t *sem4_client);
int init_client(void **shm_addr, sem_t *sem4_server, sem_t *sem4_client);
int notify_msg_sent(sem_t *sem4_id);
int receive_msg(void *shm_addr, char **msg);
int send_msg(void *shm_addr, const char *msg);
int wait_for_msg(sem_t *sem4_id);

#endif  // SHM_CHAT_H
