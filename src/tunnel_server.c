//
// Created by Gale on 2024/7/18.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "tunnel_server.h"
#include "session.h"


int init_server(uint16_t port) {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // if(!inet_aton("10.1.1.102", &server_addr.sin_addr)) {
    //     perror("converse address");
    //     exit(1);
    // }

    if(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    return sock_fd;
}


void *handle_request(void *arg) {
    int client_fd = *(int *)arg;

    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);

    while (1) {
        char buf[BUF_LEN] = {0};
        int n = recvfrom(client_fd, buf, BUF_LEN, MSG_WAITALL, (struct sockaddr*)&addr, &len);
        if (n == 0) {
            printf("client disconnect: %d\n", client_fd);
            close(client_fd);
            break;
        }

        char addr_buf[INET_ADDRSTRLEN];
        get_addr_string(addr, addr_buf);
        printf("client ip addr: %s:%d\n", addr_buf, ntohs(addr.sin_port));

        snprintf(buf, sizeof(buf), "client IP: %s:%d\n", addr_buf, ntohs(addr.sin_port));
        // strncpy(buf, addr_buf, INET_ADDRSTRLEN);

        n = sendto(client_fd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, len);

    }
}


int main() {
    int sock_fd = init_server(2000);
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);

    while(1) {
        char buf[BUF_LEN] = {0};
        pthread_t thid;
        pthread_create(&thid, NULL, handle_request, &sock_fd);
    }
}