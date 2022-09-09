#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1024

int main()
{
    int sock;
    struct sockaddr_un serv;

    char message[] = "Hello, server! ";
    char buf[SIZE];

    sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, "/tmp/stream_serv");

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