#ifndef BLACK_TUNNEL_TUNNEL_SERVER_H
#define BLACK_TUNNEL_TUNNEL_SERVER_H

#include <stdint.h>
#include <netinet/in.h>

#define CLIENT_MAX 100

typedef struct _CLIENT_TABLE {
    struct sockaddr_in addr;
    uint32_t client_id;
} client_table;


client_table clients[CLIENT_MAX] = {0};


typedef void* (*CALLBACK_FUNC)(void *arg);

#endif