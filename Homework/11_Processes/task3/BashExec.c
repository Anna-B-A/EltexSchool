#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <locale.h>
#include <string.h>



int main(void) {
    setlocale(LC_ALL, "Rus");

    pid_t pid = 0;
    int status;
    char str[50]={"\0"};
    char fileName[25]={"\0"};
    char arg1[25]={"\0"};
    char arg2[25]={"\0"};
    int i = 0;
    int j = 0;

    while(1)
    {
        strcpy (str, "\0");
        i = 0;
        j = 0;

        fgets(str, 50, stdin);

        if( 0 == strcmp(str, "exit\n"))
            break;

        for(; '\n' != str[j]; j++);
        str[j] = '\0';

        for(j=0; '\0' != str[i]; i++, j++)
        {
            if(' ' == str[i])
                break;
            fileName[j] = str[i];
        }
        fileName[j] = '\0';

        for(j = 0; '\0' != str[i]; i++, j++)
        {
            if(' ' == str[i])
                break;
            arg1[j] = str[i];
        }
        arg1[j] = '\0';

        for(j = 0; '\0' != str[i]; i++, j++)
        {
            if(' ' == str[i])
                break;
            arg2[j] = str[i];
        }
        arg2[j] = '\0';
        
        pid = fork();

        if (0 == pid) {
            char *args[]={fileName, arg1, arg2, NULL};
            execv(args[0], args);
            exit(0);
        } 
        else {
            wait(&status);
        }
        
    }
}