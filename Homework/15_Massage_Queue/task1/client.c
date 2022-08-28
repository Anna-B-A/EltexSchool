#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10


int main (void)
{
    unsigned int prio = 0;
    
    mqd_t qd_server, qd_client;

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    if ((qd_client = mq_open ("/client", O_RDONLY)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }
    if ((qd_server = mq_open ("/server", O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }

    char buf[attr.mq_msgsize];

    sprintf(buf, "Hi!");
    if (mq_send (qd_server, buf, strlen(buf), prio) == -1) {
        perror ("Client: Not able to send message to server");
        exit(1);
    }
    
    memset(buf, 0, attr.mq_msgsize);
    if (mq_receive(qd_client, buf, attr.mq_msgsize + 1, &prio) == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }

    printf("Message: %s\n", buf);

    if (mq_close(qd_server) == -1) {
        perror ("Client: mq_close server");
        exit (1);
    }
    if (mq_close(qd_client) == -1) {
        perror ("Client: mq_close client");
        exit (1);
    }

    exit(1);
}