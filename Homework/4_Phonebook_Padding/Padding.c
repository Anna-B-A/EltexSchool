#include <stdio.h>
#include <locale.h>

struct withPadding
{
    char a;
    int b;
};

struct withoutPadding
{
    char a;
    int b;
}__attribute__((packed));


int main()
{
    setlocale(LC_ALL, "Rus");

    char str[10]={'A',0,0,0,0,'B',0,0,0,0};
    struct withPadding * ptrWithPadding = (struct withPadding *) &str;
    struct withoutPadding * ptrWithoutPadding = (struct withoutPadding *) &str;

    printf("With Padding:\n");
    printf("1 object: a = %c, b = %c\n", (*ptrWithPadding).a, (*ptrWithPadding).b);
    printf("2 object: a = %c, b = %c\n\n", (*(ptrWithPadding+1)).a, (*(ptrWithPadding+1)).b);
    
    printf("Without Padding:\n");
    //лучше обращаться к полю структуры через указатель способом ниже (через ->)
    printf("1 object: a = %c, b = %c\n", ptrWithoutPadding->a, ptrWithoutPadding->b);
    printf("2 object: a = %c, b = %c\n", (ptrWithoutPadding+1)->a, (ptrWithoutPadding+1)->b);

    return 0;
}