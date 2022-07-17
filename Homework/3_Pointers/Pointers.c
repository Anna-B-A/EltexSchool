#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");

    int numberOutput = 12345678;
    char * ptrOutput = (char *) &numberOutput;
    int numberToChangeBefore = 12345678;
    int numberToChangeAfter = numberToChangeBefore;
    char * ptrToChange = (char *) &numberToChangeAfter;
    unsigned short numberByte = 1; 

    for (int i = 0; i < sizeof(numberOutput); i++)
    {
        printf("byte %d = %d\n",i, * ptrOutput);
        ptrOutput++;
    }

    printf("Введите номер байта, который надо изменить. Требуется число от 1 до 4.\n");
    scanf("%hd", &numberByte);

    switch(numberByte)
    {
        case 1:
            *(ptrToChange)+= 1;
            break;
        case 2:
            *(ptrToChange+1)+= 1;
            break;
        case 3:
            *(ptrToChange+2)+= 1;
            break;
        case 4:
            *(ptrToChange+3)+= 1;
            break;   
        default :
            printf("Надо было ввести число от 1 до 4...\n");
    }

    if(numberByte >= 1 && numberByte <= 4)
        printf("До = %d, после = %d\n",numberToChangeBefore, numberToChangeAfter);


    return 0;
}