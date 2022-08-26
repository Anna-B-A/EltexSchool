#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    int fd_fifo; /*дескриптор FIFO*/
    //char buffer[] = "Текстовая строка для fifo\n";
    char buf[100];

    /*Если файл с таким именем существует, удалим его*/
    unlink("/tmp/fifo0001.1");

    /*Создаем FIFO*/
    if ((mkfifo("/tmp/fifo0001.1", 0777)) == -1) {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(0);
    }

    /*Открываем fifo для чтения и записи*/
    if ((fd_fifo = open("/tmp/fifo0001.1", O_RDONLY)) == -1) {
        fprintf(stderr, "Невозможно открыть fifo\n");
        exit(0);
    }

    //write(fd_fifo, buffer, strlen(buffer));

    if (read(fd_fifo, &buf, sizeof(buf)) == -1)
        fprintf(stderr, "Невозможно прочесть из FIFO\n");
    else
        printf("Прочитано из FIFO : %s\n", buf);

    exit(EXIT_SUCCESS);

}