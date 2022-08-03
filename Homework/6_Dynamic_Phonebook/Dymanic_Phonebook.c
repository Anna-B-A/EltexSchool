#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>

#define FIELDLENGTH 16
#define NUMBEROFSUBSCRIBEBRS 5

struct subscriber
{
    char firstName[FIELDLENGTH];
    char lastName[FIELDLENGTH];
    char telephone[FIELDLENGTH];
} subscriber;

void printMenu();
char getValidValueOfMenu(char);
void addSubscriber(struct subscriber ** subscribers, int * size);
void showSubscribers(struct subscriber * subscribers, int * size);
void deleteSubscriber(struct subscriber ** subscribers, int * size);
void searchSubscriber(struct subscriber * subscribers, int * size);
void cleanStdin();
void cleanField(char *);

void cleanStdin()
{
    char s;
    do {
        s = getchar();
    } while ('\n' != s && EOF != s);
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

void addSubscriber(struct subscriber **subscribers, int *size)
{
    *subscribers = realloc(*subscribers, ((*size)+1) * sizeof(subscriber));

    printf("Добавление абонента:\n");
    printf("Имя: ");
    fgets(&(*subscribers)[*size].firstName, FIELDLENGTH, stdin);
    //scanf("%s", &(*subscribers)[*size].firstName);
    cleanField((char*)&(*subscribers)[*size].firstName);

    printf("Фамилия: ");
    fgets(&(*subscribers)[*size].lastName, FIELDLENGTH, stdin);
    cleanField((char*)&(*subscribers)[*size].lastName);


    printf("Номер: ");
    fgets(&(*subscribers)[*size].telephone, FIELDLENGTH, stdin);
    cleanField((char*)&(*subscribers)[*size].telephone);

    printf("Абонент успешно добавлен.\n");
    
    (*size)++;

    return;
}

void showSubscribers(struct subscriber * subscribers,int *size)
{

    printf("      Имя       |     Фамилия     |     Телефон   \n");
    
    for (int i = 0; i < *size; i++) 
    { 
        printf("%15s | %15s |%15s\n", 
            subscribers[i].firstName,
            subscribers[i].lastName,
            subscribers[i].telephone);
    }

    if(0 == *size)
    {
        printf("                    Пусто                  \n");
    }
}

void deleteSubscriber(struct subscriber ** subscribers, int *size)
{
    char deleteFirstName[FIELDLENGTH];
    printf("Для удаления абонента введите его имя: ");
    fgets(deleteFirstName, FIELDLENGTH, stdin);
    cleanField(deleteFirstName);

    for (int i = 0; i < *size; i++)
    {
        if(0 == strcmp(&(*subscribers)[i].firstName, deleteFirstName))
        {
            for (int j = i+1; j < *size; j++)
            {
                strcpy(&(*subscribers)[j-1].firstName, &(*subscribers)[j].firstName);
                strcpy(&(*subscribers)[j-1].lastName, &(*subscribers)[j].lastName);
                strcpy(&(*subscribers)[j-1].telephone, &(*subscribers)[j].telephone);
            }
            subscribers = realloc(*subscribers, (*size)*sizeof(subscriber));
            (*size)--;
            printf("Удаление прошло успешно.\n");
            return;
            
        }
    }
    printf("Не найдено абонентов с таким именем.\n");
}

void searchSubscriber(struct subscriber * subscribers, int *size)
{
    char searchFirstName[FIELDLENGTH];
    printf("Для поиска абонента введите его имя\n");
    fgets(searchFirstName, FIELDLENGTH, stdin);
    cleanField(searchFirstName);
    
    for (int i = 0; i < *size; i++)
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

    int sizePhonebook = 0;

    struct subscriber *subscribers = malloc((sizePhonebook+1) * sizeof(subscriber));

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
                addSubscriber(&subscribers, &sizePhonebook);
                break;
            case '2':
                showSubscribers(subscribers, &sizePhonebook);
                break;
            case '3':
                deleteSubscriber(&subscribers, &sizePhonebook);
                break;
            case '4':
                searchSubscriber(subscribers, &sizePhonebook);
                break;
            case '5':
                free(subscribers);
                break;
            default:
                printf("Было введено %c", selectedMenuItem);
                return 0;
        }
    }
    while(selectedMenuItem != '5');

    return 0;
}