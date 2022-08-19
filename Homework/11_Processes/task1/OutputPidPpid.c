#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid = 0;
    int status;

    printf("before the fork \n");
    pid = fork();
    
    printf("after the fork \n");
    
    if (0 == pid) {
        printf("PID child process %d\n", getpid());
        printf("PPID parent process %d\n", getppid());
        exit(0);
    }
    else {
        printf("PID parent process %d\n", getpid());
        printf("PID child process %d\n", pid);
        printf("wait\n");
        sleep(1);
        wait(&status);
        printf("exit b\n");
        sleep(1);
        exit(0);
    }
}