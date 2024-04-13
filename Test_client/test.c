#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 49155
#define MAXLINE 1000

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Создание сокета UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Используйте адрес вашего сервера

    // Отправка сообщения на сервер
    while(1){
        memset(buffer, 0, MAXLINE);
        fgets(buffer, MAXLINE, stdin);
        if(sendto(sockfd, buffer, strlen(buffer) - 1, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
                perror("recvfrom failed");
                printf("%s\n", strerror(errno));
                break;
            }
        if(strcmp(buffer, "stop\n") == 0){
            break;
        }
    }

    if(sockfd) close(sockfd);
}