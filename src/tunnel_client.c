#include <stdio.h>
#include <sys/socket.h>
#include <stdint.h>
#include <netinet/in.h>
#include <unistd.h>

#include "session.h"


int main() {
    struct sockaddr_in client_addr;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(2000);

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    socklen_t len = sizeof(client_addr);

    while(1) {
        char buf[BUF_LEN] = {0};

        // TODO 将自己的IP地址和端口号发送出去
        int num = sendto(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_in));
        if (num < 0) {
            perror("sendto");
            break;
        }

        num = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &len);

        if (num < 0) {
            perror("recvfrom");
            break;
        } else {
            printf("recvfrom: %s\n", buf);
        }

    }

    close(sock_fd);

}