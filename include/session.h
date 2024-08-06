//
// Created by Gale on 2024/8/6.
//

#ifndef BLACK_TUNNEL_SESSION_H
#define BLACK_TUNNEL_SESSION_H
#include <stdint.h>
#include <netinet/in.h>

#define BUF_LEN                 512
#define CLIENT_MAX              1024
#define CLIENT_ADDR_LENGTH		6

typedef struct {
    unsigned char * server_addr;
    uint16_t port;

    int sock_fd;
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    char buf[BUF_LEN];
} Sess;


#define LOGIN_REQ  0x01

int client_count = 0;

typedef volatile long UATOMIC;
typedef unsigned char U8;
typedef unsigned char U16;
typedef unsigned char U32;


typedef struct _CLIENT_TABLE {
    U8 addr[CLIENT_ADDR_LENGTH];
    U32 client_id;
    long stamp;
} client_table;

client_table table[CLIENT_MAX] = {0};


typedef enum {
    CLIENT_HANDLE_FAILED = -1,
    CLIENT_HANDLE_SUCCESS = 0,
} HANDLE_RESULT;

/****************************content define ***************************/
#define BUFFER_VERSION_IDX     0
#define BUFFER_STATUS_IDX      1
#define BUFFER_LENGTH_IDX      (BUFFER_STATUS_IDX+1)
#define BUFFER_CLIENT_IDX      (BUFFER_STATUS_IDX+2)


// login
#define BUFFER_LOGIN_ID_IDX    BUFFER_CLIENT_IDX

// heartbeat
#define HEADRTBEAT_CLIENT_ID_IDX  BUFFER_CLIENT_IDX


static unsigned long cmpxchg(UATOMIC *addr, unsigned long _old, unsigned long _new) {
    U8 res;

    __asm__ volatile (
            "lock; cmpxchg %3, %1;sete %0;"
            : "=a" (res)
            : "m" (*addr), "a" (_old), "r" (_new)
            : "cc", "memory");

    return res;
}


static int addr_to_array(U8 *array, struct sockaddr_in *p_addr) {
    int i = 0;

    for (i = 0; i < 4; i++) {
        array[i] = *((unsigned char*)(&p_addr->sin_addr.s_addr) + i);
    }

    for (i = 0; i < 2; i++) {
        array[4+i] = *((unsigned char*)(&p_addr->sin_port) + i);
    }
}


void get_addr_string(struct sockaddr_in *addr, char buf[INET_ADDRSTRLEN]);

#endif