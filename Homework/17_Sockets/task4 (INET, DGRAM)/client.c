#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in serv;

    char message[] = "Hello, Server!";
    char buf[SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(3425); 
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }

    if(send(sock, message, strlen(message), 0) < 0) {
        perror("send");
        exit(1);
    }

    int bytes_read = recv(sock, buf, sizeof(buf), 0);
    if(bytes_read >= 0) 
        printf("%s", buf);
    else {
        perror("recv");
        exit(1);
    }

    close(sock);

    exit(1);
}