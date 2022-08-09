#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void ReverseOutput(int);

void ReverseOutput(int fd)
{
    char c[1] = "";
    int size = lseek(fd, 0, SEEK_END);

    for(int i = size; i > 0; i--) {
        read(fd, c, sizeof(c));
        printf("%s", c);
        lseek(fd, -2, SEEK_CUR);
    }
}

int main(void)
{
    int fd;
    char strw[]={"Hello, World!"};
    char strr[30]={'0'};

    if ((fd = open("file.txt", O_CREAT| O_RDWR ))==-1) {
        printf ("Cannot open file.\n");
        exit(1);
        }

    write(fd, strw, sizeof(strw));
    
    lseek(fd, 0, SEEK_SET);

    ReverseOutput(fd);

    /*read(fd, strr, sizeof(strr));
    puts(strr);*/

    close(fd);

    return 0;
}