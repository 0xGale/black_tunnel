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
#include <stdlib.h>

#include "session.h"


int init_server(uint16_t port) {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(port);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind");
        exit(1);
    }

    return sock_fd;
}


// 解析客户端的所有请求, 该请求中包含了多个命令
int buffer_parser(int sockfd, U8 *buffer, uint32_t length, struct sockaddr_in *addr) {
    U8 status = buffer[BUFFER_STATUS_IDX];
//    printf("buffer parser --> %x\n", status);
    switch (status) {
        case LOGIN_REQ:
            int old = client_count;
            int now = old + 1;
//            if(0 == cmpxchg((UATOMIC*)&client_count, old, now)) {
//                printf("client_count --> %d, old:%d, now:%d\n", client_count, old, now);
//                return CLIENT_HANDLE_FAILED;
//            }
            U8 array[CLIENT_ADDR_LENGTH] = {0};
            addr_to_array(array, addr);
            char addr_buf[INET_ADDRSTRLEN];
            get_addr_string(addr, addr_buf);
            printf("client id: %d, \t", *(U32*)(buffer+BUFFER_LOGIN_ID_IDX));
            printf("client public ip client_addr: %s:%d\n", addr_buf, ntohs(addr->sin_port));;
            table[now].client_id = *(U32*)(buffer+BUFFER_LOGIN_ID_IDX);
            memcpy(table[now].addr, array, CLIENT_ADDR_LENGTH);
            break;
    }
}

void *handle_request(void *arg) {
    int client_fd = *(int *)arg;

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    U8 client_buf[BUF_LEN] = {0};
    char addr_buf[INET_ADDRSTRLEN];
    ssize_t n;

    while (1) {
        n = recvfrom(client_fd, client_buf, BUF_LEN, MSG_WAITALL, (struct sockaddr*)&client_addr,
                &len);
        if (n == 0) {
            printf("client closed: %d\n", client_fd);
            close(client_fd);
            break;
        } else if (n > 0) {
            // snprintf(buf, sizeof(buf), "client IP: %s:%d\n", addr_buf, ntohs(client_addr.sin_port));
            int ret = buffer_parser(client_fd, client_buf, n, &client_addr);
            if (ret == CLIENT_HANDLE_FAILED)
                continue;

            client_buf[BUFFER_STATUS_IDX] += 0x80;
            n = sendto(client_fd, client_buf, BUF_LEN, 0, (struct sockaddr*)&client_addr,
                    sizeof(client_addr));
            if (n < 0) {
                perror("sendto");
                break;
            }
        }

    }
    close(client_fd);
}


int main() {
    int sock_fd = init_server(2000);

    pthread_t thid;
    pthread_create(&thid, NULL, handle_request, &sock_fd);
    pthread_join(thid, NULL);
}