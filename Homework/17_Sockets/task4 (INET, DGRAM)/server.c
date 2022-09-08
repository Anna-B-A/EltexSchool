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
    socklen_t size;
    struct sockaddr_in serv, client;
    
    char buf[SIZE];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) {
        perror("socket");
        exit(1);
    }
    
    serv.sin_family = AF_INET;
    serv.sin_port = htons(3425);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind");
        exit(1);
    }

    size = sizeof(client);

    int bytes_read = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client, &size);
    if(bytes_read >= 0) {
        printf("Message from client: %s\n",buf);
        strcat(buf, " Answer Server!\n"); 
        if(sendto(sock, buf, strlen(buf), 0, (struct sockaddr *)&client, size) < 0) {
            perror("sendto");
            exit(1);
        }
    }
    else {
        perror("recvfrom");
        exit(1);
    }

    close(sock);
    
    exit(1);
}