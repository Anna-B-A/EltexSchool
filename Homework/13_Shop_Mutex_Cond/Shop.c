#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#define MAXMAG 1100
#define MINMAG 900
#define MAXCUST 10500
#define MINCUST 9500
#define LOADER 500
#define NUMMAG 5 
#define NUMCUST 3

struct Cust
{
    int id, money;
};

struct Cust custData[NUMCUST];
pthread_mutex_t mag[NUMMAG];
int magGoods[NUMMAG];
int lastCust = 0;

void * Shopping(void * arg)
{
    struct Cust * custData = (struct Cust*) arg;
    int choiceMag;

    printf("У клиента %d есть %d денег\n", custData->id, custData->money);

    while (custData->money > 0)
    {
        choiceMag = rand()%NUMMAG;
        pthread_mutex_lock(&mag[choiceMag]);
        if (0 == magGoods[choiceMag]) {
            printf("Клиент %d зашел в пустой магазин %d\n", custData->id, choiceMag);
            sleep(3);
        }
        else {
            if (custData->money - magGoods[choiceMag] >= 0) {
                custData->money -= magGoods[choiceMag];
                magGoods[choiceMag] = 0;
                printf("Клиент %d опустошил %d магазин. У него осталось %d денег\n",
                custData->id, choiceMag, custData->money);
            }
            else {
                custData->money = 0;
                magGoods[choiceMag] -= custData->money;
                printf("У клиента %d закончились деньги после покупки в магазине %d\n", 
                custData->id, choiceMag);
            }
        }
        pthread_mutex_unlock(&mag[choiceMag]);
        sleep(3);
    }
    lastCust++;
    pthread_exit(NULL);
}

void * Loading(void * arg)
{
    int choiceMag;
    while (lastCust < NUMCUST) {
        choiceMag = rand()%NUMMAG;
        pthread_mutex_lock(&mag[choiceMag]);
        magGoods[choiceMag] += LOADER;
        printf("Загрузчик заполнил магазин %d\n", choiceMag);
        pthread_mutex_unlock(&mag[choiceMag]);
        sleep(1);
    }
    pthread_exit(NULL);
}


int main(void)
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");


    int* status;

    for (int i = 0; i < NUMMAG; i++) {
        magGoods[i] = rand()%(MAXMAG-MINMAG)+MINMAG;
    }

    for (int i = 0; i < NUMCUST; i++) {
        custData[i].money = rand()%(MAXCUST-MINCUST)+MINCUST;
        custData[i].id = i;
    }

    pthread_t cust[NUMCUST], loader;
    for (int i = 0; i < NUMCUST; i++) {
        pthread_create(&cust[i], NULL, Shopping, (void*)&custData[i]);
    }
    pthread_create(&loader, NULL, Loading, NULL);

    for (int i = 0; i < NUMCUST; i++){
        pthread_join(cust[i], (void **) &status);
    }
    pthread_join(loader, (void **) &status);

    for (int i = 0; i < NUMMAG; i++) {
        pthread_mutex_destroy(&mag[i]);
    }
     
    exit(1);
}