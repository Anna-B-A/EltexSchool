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
    int sock, listener;
    socklen_t size;
    struct sockaddr_in serv, client;
    char buf[SIZE];

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0) {
        perror("socket");
        exit(1);
    }
    
    serv.sin_family = AF_INET;
    serv.sin_port = htons(3425);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind");
        exit(1);
    }

    if(listen(listener, 1) < 0) {
        perror("listen");
        exit(1);
    }
    
    size = sizeof(client);

    sock = accept(listener, (struct sockaddr *)&client, &size);
    if(sock < 0) {
        perror("accept");
        exit(1);
    }

    int bytes_read = recv(sock, buf, sizeof(buf), 0);
    if(bytes_read >= 0) {
        printf("Message from client: %s\n",buf);
        strcat(buf, " Answer Server!\n"); 
        if(send(sock, buf, strlen(buf), 0) < 0) {
            perror("send");
            exit(1);
        }
    }
    else {
        perror("recv");
        exit(1);
    }

    close(sock);
    close(listener);
    
    exit(1);
}