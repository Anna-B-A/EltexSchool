#include <stdio.h>
#include <locale.h>
#include <string.h>

#define FIELDLENGTH 16
#define NUMBEROFSUBSCRIBEBRS 5

struct subscriber
{
    char firstName[FIELDLENGTH];
    char lastName[FIELDLENGTH];
    char telephone[FIELDLENGTH];
};

void printMenu();
char getValidValueOfMenu(char);
void addSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS]);
void showSubscribers(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS]);
void deleteSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS]);
void searchSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS]);
void cleanStdin();
void cleanField(char *);

void cleanStdin()
{
    int s;
    do {
    s = getchar();
    } while (s != '\n' && s != EOF);
}

void cleanField(char * field)
{
    while ('\0' != *field){
        if ('\n' == *field){
            *field = '\0';
            break;
        }
        field++;
    }
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

void addSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS])
{
    for (int i = 0; i < NUMBEROFSUBSCRIBEBRS; i++)
    {
        if(0 == strcmp(subscribers[i].telephone, "\0"))
        {
            printf("Добавление абонента:\n");
            printf("Имя: ");
            fgets(subscribers[i].firstName, FIELDLENGTH, stdin);
            cleanField((char*)&subscribers[i].firstName);

            printf("Фамилия: ");
            fgets(subscribers[i].lastName, FIELDLENGTH, stdin);
            cleanField((char*)&subscribers[i].lastName);

            printf("Номер: ");
            fgets(subscribers[i].telephone, FIELDLENGTH, stdin);
            cleanField((char*)&subscribers[i].telephone);

            printf("Абонент успешно добавлен.\n");
            return;
        }
    }
    printf("Нет свободного места.\n");
}

void showSubscribers(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS])
{
    int size = 0;

    printf("      Имя       |     Фамилия     |     Телефон   \n");
    
    for (int i = 0; i < NUMBEROFSUBSCRIBEBRS; i++) 
    { 
        if(0 != strcmp(subscribers[i].telephone, "\0"))
        { 
            size++;
            printf("%15s | %15s |%15s\n", 
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

void deleteSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS])
{
    char deleteFirstName[FIELDLENGTH];
    printf("Для удаления абонента введите его имя: ");
    fgets(deleteFirstName, FIELDLENGTH, stdin);
    cleanField(deleteFirstName);

    for (int i = 0; i < NUMBEROFSUBSCRIBEBRS; i++)
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

void searchSubscriber(struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS])
{
    char searchFirstName[FIELDLENGTH];
    printf("Для поиска абонента введите его имя\n");
    fgets(searchFirstName, FIELDLENGTH, stdin);
    cleanField(searchFirstName);
    
    for (int i = 0; i < NUMBEROFSUBSCRIBEBRS; i++)
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

    struct subscriber subscribers[NUMBEROFSUBSCRIBEBRS] = {'\0'};

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