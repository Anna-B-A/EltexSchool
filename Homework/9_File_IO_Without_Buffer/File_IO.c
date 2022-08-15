#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void ReverseOutput(int);

void ReverseOutput(int fd)
{
    char c = 'a';
    
    //1 solution
    /*
    int size = lseek(fd, 0, SEEK_END);

    for(int i = size; i > 0; i--) {        
        read(fd, &c, sizeof(c));
        printf("%c", c);
        lseek(fd, -2, SEEK_CUR);
    }*/
    
    //2 solution
    int size = lseek(fd, -1, SEEK_END);

    for(int i = size-1; i >= 0; i--) {    
        lseek(fd, i, SEEK_SET);
        read(fd, &c, sizeof(c));
        printf("%c", c);
    }
}

int main(void)
{
    int fd;
    char strw[]={"Hello, World!\0"};
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