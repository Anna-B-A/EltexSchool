#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");

    int numberOutput = 0xAABBCCDD;
    int numberToChangeBefore = 0xAABBCCDD;
    int numberToChangeAfter = 0xAABBCCDD;
    unsigned short numberByte = 1; 

    for (int i = 0; i < sizeof(numberOutput); i++)
    {
        printf("byte %d = %x\n",i, (numberOutput & 0xFF));
        numberOutput = numberOutput >> 8;
    }

    printf("Введите номер байта, который надо изменить. Требуется число от 1 до 4.\n");
    scanf("%hd", &numberByte);

    switch( numberByte)
    {
        case 1:
            numberToChangeAfter^= 0xff000000;
            break;
        case 2:
            numberToChangeAfter^= 0xff0000;
            break;
        case 3:
            numberToChangeAfter^= 0xff00;
            break;
        case 4:
            numberToChangeAfter^= 0xff;
            break;   
        default :
            printf("Надо было ввести число от 1 до 4...\n");
    }

    if(numberByte >= 1 && numberByte <= 4)
        printf("До = %x, после = %x\n",numberToChangeBefore, numberToChangeAfter);


    return 0;
}