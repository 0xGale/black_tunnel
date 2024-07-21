// #include <errno.h>
// #include <string.h>
// #include <stdio.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <pthread.h>
// #include <unistd.h>
// #include <sys/epoll.h>
// #include <arpa/inet.h>


// void *handle_client(void *arg) {

// }


// int init_server(unsigned short port) {
//     int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

//     struct sockaddr_in servaddr;

//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
//     servaddr.sin_port = htons(port);

//     if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) == -1) {
//         printf("bind failed: %s\n", strerror(errno));
//     }
//     return sockfd;
// }

// int main(int argv, char *argc[]) {
//     struct sockaddr_in clientaddr;
//     char buf[1024] = {0};
//     int sockfd = init_server(2000);
//     int len = sizeof(struct sockaddr_in);

//     while(1) {
//         bzero(buf, sizeof(buf));
//         int n = recvfrom(sockfd, buf, 10, MSG_WAITALL, (struct sockaddr*)&clientaddr, &len);
//         printf("sock_fd: %d\n", sockfd);

//         printf("n: %d\n", n);
//         if(n < 0) {
//             perror("recvfrom\n");
//         }
//         char client_ip[INET_ADDRSTRLEN];
//         inet_ntop(AF_INET, &clientaddr.sin_addr, client_ip, INET_ADDRSTRLEN);
//         printf("recv from: %s:%d\n", client_ip, ntohs(clientaddr.sin_port));

//         // size_t num_bytes = sendto(server_fd, "hello world", 11, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
//         char response[1024];
//         snprintf(response, 1024, "recv from: %s:%d, data: %s\n", client_ip, ntohs(clientaddr.sin_port), buf);
//         printf(response);
//         n = sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
//         if(n < 0) {
//             perror("sentdo\n");
//         }
//     }
//     close(sockfd);

// }