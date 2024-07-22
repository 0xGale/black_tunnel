#include <stdio.h>
#include <sys/socket.h>
#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "session.h"
#include "tunnel_client.h"


int login_server(int sockfd, int client_id, struct sockaddr_in *server_addr) {
    uint8_t buffer[BUF_LEN] = {0};

    buffer[BUFFER_STATUS_IDX] = LOGIN_REQ;
    *(uint32_t *)(buffer+BUFFER_LOGIN_ID_IDX) = client_id;

    int n = BUFFER_LOGIN_ID_IDX + 4;  // client_id所占的空间 + 头部长度
    n = sendto(sockfd, buffer, n, 0, (struct sockaddr*)server_addr, sizeof(struct sockaddr_in));

    if (n < 0) {
        perror("sendto");
    }

    return n;
}


void *send_callback(void *argv) {

}


void *recv_callback(void *argv) {

}


int main(int argc, char *argv[]) {
    struct sockaddr_in server_addr;
    // client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t len = sizeof(server_addr);
    int client_id = atoi(argv[3]);


    pthread_t threads[2] = {0};

    CALLBACK_FUNC cb[2] = {send_callback, recv_callback};

    for (int i = 0; i < 2; i++) {
        int ret = pthread_create(&threads[i], NULL, cb[i], &sock_fd);
        if (ret) {
            perror("pthread_create");
            exit(1);
        }
        sleep(1);
    }

    login_server(sock_fd, client_id, &server_addr);


    for (int i=0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    } 



    // while(1) {
    //     char buf[BUF_LEN] = {0};

    //     // TODO 将自己的IP地址和端口号发送出去
    //     int num = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in));
    //     if (num < 0) {
    //         perror("sendto");
    //         break;
    //     }

    //     num = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);

    //     if (num < 0) {
    //         perror("recvfrom");
    //         break;
    //     } else {
    //         printf("recvfrom: %s\n", buf);
    //     }

    // }

    close(sock_fd);

}