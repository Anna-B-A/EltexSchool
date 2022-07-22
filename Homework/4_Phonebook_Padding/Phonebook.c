#include <stdio.h>
#include <locale.h>
#include <string.h>

#define fieldLength 16
#define numberOfSubscribers 5

struct subscriber
{
    char firstName[fieldLength];
    char lastName[fieldLength];
    char telephone[fieldLength];
};

void printMenu();
char getValidValueOfMenu(char);
void addSubscriber(struct subscriber subscribers[numberOfSubscribers]);
void showSubscribers(struct subscriber subscribers[numberOfSubscribers]);
void deleteSubscriber(struct subscriber subscribers[numberOfSubscribers]);
void searchSubscriber(struct subscriber subscribers[numberOfSubscribers]);
void cleanStdin();

void cleanStdin()
{
    int s;
    do {
    s = getchar();
    } while (s != '\n' && s != EOF);
}

void printMenu()
{
    printf("Введите номер действия:\n");
    printf("1 - Добавить абонента\n");
    printf("2 - Просмотреть список абонентов\n");
    printf("3 - Удалить абонента\n");
    printf("4 - Найти абонента\n"); 
    printf("5 - Выйти\n");
}

char checkValidValueOfMenu(char itemOfMenu)
{
    while(itemOfMenu < '1' || itemOfMenu > '5')
    {
        printf("Введите значение от 1 до 5 (номер действия)\n");
        itemOfMenu = getchar();
        cleanStdin();
    }
    return itemOfMenu;
}

void addSubscriber(struct subscriber subscribers[numberOfSubscribers])
{
    for (int i = 0; i < numberOfSubscribers; i++)
    {
        if(0 == strcmp(subscribers[i].telephone, "\0"))
        {
            printf("Добавление абонента:\n");
            printf("Имя: ");
            fgets(subscribers[i].firstName, fieldLength, stdin);

            printf("Фамилия: ");
            fgets(subscribers[i].lastName, fieldLength, stdin);

            printf("Номер: ");
            fgets(subscribers[i].telephone, fieldLength, stdin);

            printf("Абонент успешно добавлен.\n");
            return;
        }
    }
    printf("Нет свободного места.\n");
}

void showSubscribers(struct subscriber subscribers[numberOfSubscribers])
{
    int size = 0;

    printf("      Имя       |     Фамилия     |     Телефон   \n");

    for (int i = 0; i < numberOfSubscribers; i++)
    {
        if(0 != strcmp(subscribers[i].telephone, "\0"))
        {
            size++;
            printf("%14s | %14s | %14s\n", 
                subscribers[i].firstName,
                subscribers[i].lastName,
                subscribers[i].telephone);
        }
    }

    if(0 == size)
    {
        printf("                    Пусто                  \n");
    }
}

void deleteSubscriber(struct subscriber subscribers[numberOfSubscribers])
{
    char deleteFirstName[fieldLength];
    printf("Для удаления абонента введите его имя: ");
    fgets(deleteFirstName, fieldLength, stdin);
    fflush(stdin);
    for (int i = 0; i < numberOfSubscribers; i++)
    {
        if(0 == strcmp(subscribers[i].firstName, deleteFirstName))
        {
            strcpy(subscribers[i].firstName,"\0");
            strcpy(subscribers[i].lastName,"\0");
            strcpy(subscribers[i].telephone,"\0");
            printf("Удаление прошло успешно.");
            return;
        }
    }
    printf("Не найдено абонентов с таким именем.");
}

void searchSubscriber(struct subscriber subscribers[numberOfSubscribers])
{
    char searchFirstName[fieldLength];
    printf("Для поиска абонента введите его имя\n");
    fgets(searchFirstName, fieldLength, stdin);
    fflush(stdin);
    
    for (int i = 0; i < numberOfSubscribers; i++)
    {
        if(0 == strcmp(subscribers[i].firstName, searchFirstName))
        {
            printf("Найден:\n\t%s\t%s\t%s", 
                subscribers[i].firstName,
                subscribers[i].lastName,
                subscribers[i].telephone);
            return;
        }
    }
    printf("Не найдено абонентов с таким именем.\n");
}

int main()
{
    setlocale(LC_ALL, "Rus");

    struct subscriber subscribers[numberOfSubscribers] = {'\0'};

    char selectedMenuItem = '0';

    do
    {
        printMenu();
        selectedMenuItem = getchar();
        cleanStdin();
        selectedMenuItem = checkValidValueOfMenu(selectedMenuItem);
        switch (selectedMenuItem)
        {
            case '1':
                addSubscriber(subscribers);
                break;
            case '2':
                showSubscribers(subscribers);
                break;
            case '3':
                deleteSubscriber(subscribers);
                break;
            case '4':
                searchSubscriber(subscribers);
                break;
            case '5':
                break;
            default:
                printf("Было введено %c", selectedMenuItem);
                return 0;
        }
    }
    while(selectedMenuItem != '5');

    return 0;
}