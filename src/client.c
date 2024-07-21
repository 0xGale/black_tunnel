// #include <stdio.h>
// #include <error.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>


// int main(int argc, char *argv[]) {
//     struct sockaddr_in server_addr;
//     char buffer[1024];
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(2000);

//     socklen_t addr_len = sizeof(server_addr);

//     if (inet_pton(AF_INET, "106.75.252.148", &server_addr.sin_addr) <= 0) {
//         perror("inet_pton");
//         return 0;
//     }

//     int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
//     while(1) {
//         sleep(1);
//         size_t num_bytes = sendto(server_fd, "hello world", 11, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
//         if(num_bytes < 0) {
//             perror("recfrom\n");
//             return 0;
//         }
//         printf("recfrom\n");

//         num_bytes = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&server_addr, &addr_len);
//         if (num_bytes < 0) {
//             perror("recvfrom");
//         }

//         buffer[num_bytes] = '\0'; // 确保缓冲区以 NULL 结尾
//         printf("Received message: %s\n", buffer);


//     }
//     // 关闭套接字
//     close(server_fd);

//     return 0;
// }


// // TODO 测试一下 