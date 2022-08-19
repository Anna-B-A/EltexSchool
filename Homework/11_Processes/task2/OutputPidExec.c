#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    pid_t pid = 0;
    int status;

    pid = fork();
    if (0 == pid) {

        char *args[]={"./exec", NULL};
        execv(args[0],args);
        exit(0);
    } 
    else {
        printf("Child PID is: %d\n", pid);
        printf("PID parent process %d\n", getpid());
        wait(&status);
        exit(0);
    }
}