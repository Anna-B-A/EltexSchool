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
    struct sockaddr_un serv, client;

    char message[] = "Hello, server! ";
    char buf[SIZE];

    sock = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }

    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, "/tmp/serv");
    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, "/tmp/client");
    unlink(client.sun_path);

    if(bind(sock, (struct sockaddr *)&client, sizeof(client)) < 0) {
        perror("bind");
        exit(1);
    }

    if(connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }

    if(send(sock, message, strlen(message), 0) < 0) {
        perror("send");
        exit(1);
    }

    int bytes_read = recv(sock, buf, SIZE, 0);
    if(bytes_read >= 0) 
        printf("%s", buf);
    else {
        perror("recv");
        exit(1);
    }
    
    close(sock);
    unlink(client.sun_path);

    exit(1);
}