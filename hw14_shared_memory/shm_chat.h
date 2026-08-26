#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define PROJ_ID 1
#define SERVER_FILENAME "./sysv_server.exe"

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

void *attach_shm_segment(int shm_id);
void cleanup(int shm_id, void *shm_addr, int sem4_id, char *reply);
void destroy_semaphore(int sem4_id);
void destroy_shm_segment(int shm_id);
void detach_shm_segment(void *shm_addr);
int init_chat(int *shm_id, void **shm_addr, int *sem4_id);
int receive_msg(void *shm_addr, char **msg);
int send_msg(void *shm_addr, char *msg);
void set_state(int sem4_id, int value);

#endif  // SHM_CHAT_H
