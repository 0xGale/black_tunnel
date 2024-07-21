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


void get_addr_string(struct sockaddr_in addr, char buf[INET_ADDRSTRLEN]);

#endif