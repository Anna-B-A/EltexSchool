#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>

#define MAX_NAME 10

unsigned int prio = 0;

void cleanStr(char *);
void * read(void *);

void cleanStr(char * str)
{
    while ('\0' != *str) {
        if ('\n' == *str) {
            *str = '\0';
            break;
        }
        str++;
    }
}

void * read(void * arg)
{
    mqd_t * qd_client = (mqd_t *)arg;

    struct mq_attr attr;
    mq_getattr(*qd_client, &attr);

    char buf[attr.mq_msgsize];
    printf("%ls hehehehhe\n", qd_client);

    while(1) {
        ssize_t bytes = mq_receive(*qd_client, buf, attr.mq_msgsize + 1, &prio);
        if (bytes == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }
        if (bytes > 0)
        {
            printf("%s\n", buf);
            memset(buf, 0, attr.mq_msgsize);
        }          
    }

}

int main (void)
{    
    mqd_t qd_server, qd_client;

    if ((qd_server = mq_open ("/server", O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }
    if ((qd_client = mq_open ("/client", O_RDONLY)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }

    pthread_t rd;
    pthread_create(&rd, NULL, read, (void*)&qd_client);

    struct mq_attr attr;
    mq_getattr(qd_server, &attr);

    char buf[attr.mq_msgsize];
    char name[MAX_NAME];
    char text[attr.mq_msgsize - MAX_NAME];

    puts("Enter your name (no more than 10 characters): ");
    fgets(name, MAX_NAME, stdin);
    cleanStr(name);

    while(1) {
        memset(text, 0, attr.mq_msgsize - MAX_NAME);
        fgets(text, attr.mq_msgsize - MAX_NAME, stdin);
        cleanStr(text);

        if(0 != strcmp(text, "exit"))
            break;

        strcat(buf, name);
        strcat(buf, ": ");
        strcat(buf, text);

        if (mq_send (qd_server, buf, strlen(buf), prio) == -1) {
            perror ("Client: Not able to send message to server");
            exit(1);
        }

        memset(buf, 0, attr.mq_msgsize);
    }

    if (mq_close(qd_server) == -1) {
        perror ("Client: mq_close server");
        exit (1);
    }
    if (mq_close(qd_client) == -1) {
        perror ("Client: mq_close client");
        exit (1);
    }

    pthread_join(rd, NULL);

    exit(1);
}