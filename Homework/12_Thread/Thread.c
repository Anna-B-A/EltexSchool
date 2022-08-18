#include <pthread.h>
#include <stdio.h>

int a = 0;

void *func(void *args)
{
    for (int temp, i = 0; i < 1000000; i++) {
        temp = a;
        temp++;
        a=temp; 
    }
}

int main()
{
    pthread_t tid[20];
    int *status;
    int index[20];

    for(int i = 0; i < 20; i++)
    {
        index[i] = i + 1;
        pthread_create(&tid[i], NULL, func, (void*) &index[i]);
    }
    for (int i = 0; i < 20; i++) {
        pthread_join(tid[i], (void**) &status);
    }

    printf("%d", a);

    return 0;
}
