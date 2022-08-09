#include "actions.h"
#include <stdio.h>

void printMenu()
{
    printf("Введите номер действия:\n");
    printf("1 - Сложение\n");
    printf("2 - Вычитание\n");
    printf("3 - Умножение\n");
    printf("4 - Деление\n"); 
    printf("5 - Выйти\n");
}

int main(void)
{
    int selectedMenuItem = 0;
    int arg1 = 0;
    int arg2 = 0;

    do
    {
        printMenu();
        scanf("%d", &selectedMenuItem);
        
        if (5==selectedMenuItem)
        {
            puts("До связи\n");
            return 0;
        }

        puts("Введите значение первого аргумента");
        scanf("%d", &arg1);

        puts("Введите значение второго аргумента");
        scanf("%d", &arg2);

        switch (selectedMenuItem)
        {
            case 1:
                printf("Результат: %d\n", add(arg1,arg2));
                break;
            case 2:
                printf("Результат: %d\n", sub(arg1,arg2));
                break;
            case 3:
                printf("Результат: %d\n", mult(arg1,arg2));
                break;
            case 4:
                printf("Результат: %d\n", div(arg1,arg2));
                break;
            default:
                printf("Было введено %d", selectedMenuItem);
                return 0;
        }
    }
    while(selectedMenuItem != 5);
}