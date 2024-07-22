#ifndef _BLACK_TUNNEL_SESSION
#define _BLACK_TUNNEL_SESSION
#include <stdint.h>
#include <netinet/in.h>

#define BUF_LEN 512

typedef struct {
    unsigned char * server_addr;
    uint16_t port;

    int sock_fd;
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    char buf[BUF_LEN];
} Sess;

#define LOGIN_REQ  0x01



/****************************content define ***************************/
#define BUFFER_VERSION_IDX     0
#define BUFFER_STATUS_IDX      1
#define BUFFER_LENGTH_IDX      (BUFFER_STATUS_IDX+1)
#define BUFFER_CLIENT_IDX      (BUFFER_STATUS_IDX+2)


// login
#define BUFFER_LOGIN_ID_IDX    BUFFER_CLIENT_IDX

// heartbeat
#define HEADRTBEAT_CLIENT_ID_IDX  BUFFER_CLIENT_IDX



void get_addr_string(struct sockaddr_in addr, char buf[INET_ADDRSTRLEN]);

#endif