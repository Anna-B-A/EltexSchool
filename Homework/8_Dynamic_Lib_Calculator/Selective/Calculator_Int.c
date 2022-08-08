#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int (*func_ptr[argc])(int*,int*);
    void (*text_func_ptr[argc])(void);

    for (int i=1; i < argc; i++) {
        
        void * library_handler = dlopen(argv[i], RTLD_LAZY);

        if (!library_handler){
            fprintf(stderr,"dlopen() error: %s\n", dlerror());
            exit(1); 
        }
      
        text_func_ptr[i] = (void (*)(void))dlsym(library_handler, "text");
        func_ptr[i] = (int (*)(int*,int*))dlsym(library_handler, "func");

        if (!func_ptr[i] || !text_func_ptr[i]){
            fprintf(stderr,"dlsym() error: %s\n", dlerror());
            exit(1); 
        }
    }
    
    int selectedMenuItem = 0, arg1 = 0, arg2 = 0;

    while(1)
    {
        printf("Введите номер действия:\n");

        for (int i=1; i < argc; i++) {
            text_func_ptr[i]();
        }
        puts("5 - Выход\n");

        scanf("%d", &selectedMenuItem);
        
        if (selectedMenuItem < 1 || selectedMenuItem > argc)
        {
            puts("Вы хотите выйти? (y/n)\n");
            char choice = 'n';
            scanf("%c", &choice);
            getchar();
            if('y' == choice) {
                return 0;
            }
        }

        puts("Введите значение первого аргумента");
        scanf("%d", &arg1);

        puts("Введите значение второго аргумента");
        scanf("%d", &arg2);

        printf("Результат: %d\n", func_ptr[selectedMenuItem](&arg1,&arg2));
    }

    return 0;
}
