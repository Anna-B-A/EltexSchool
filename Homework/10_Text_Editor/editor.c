#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <locale.h>
#include <fcntl.h>

void sig_winch(int);
void Menu();
void InputMode();
void Open();
void Save();

void sig_winch(int signo)
{
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}

void Menu()
{
    move(1, 3);
    printw("F1 - Открыть файл\n");
    move(2, 3);
    printw("F2 - Сохранить файл\n");
    move(3, 3);
    printw("F3 - Выход\n");
    move(5, 3);
    attron(A_BLINK);
    printw("Введите любой символ для продолжения...");
    attroff(A_BLINK);
    refresh();
}

void InputMode()
{
    int x = 0, y = 0;
    getyx(stdscr, y, x);
    echo();
    curs_set(1);
    switch (wgetch(stdscr))
    {
    case KEY_F(1):
        clear();
        Open();
        break;
    case KEY_F(2):
        Save();
        break;
    case KEY_F(3):
        endwin();
        exit(EXIT_SUCCESS);
    case KEY_BACKSPACE:
        delch();
        break;
    case KEY_UP:
        move(y-1, 0);
        break;
    case KEY_DOWN:
        move(y+1, 0);
        break;
    case KEY_LEFT:
        move(y, x-1);
        break;
    case KEY_RIGHT:
        move(y, x+1);
        break;
    }
}

void Open()
{
    //work
    FILE * fd;
    char c[2];
    if ((fd = fopen("file.txt", "rw"))==NULL) {
        printf ("Cannot open file.\n");
        exit(1);
    }

    while(!feof(fd))
    {
        fgets(c, 2, fd);
        printw("%s", c);
    }

    fclose(fd);
    wmove(stdscr, 0, 0);

    //no work
    /*int fd;
    char c = 'a';
    if ((fd = open("file.txt", O_CREAT| O_RDWR ))==-1) {
        printf ("Cannot open file.\n");
        exit(1);
    }

    int size = lseek(fd, 0, SEEK_SET);

    for(int i = 0; i < size; i++) {    
        read(fd, &c, sizeof(c));
        printw("%c", c);
    }

    close(fd);
    */
}

void Save()
{
    //work
    int h, w, ys, xs, lastnospace;
    FILE * fd;
    if ((fd = fopen("file.txt", "w"))==NULL) {
        printf ("Cannot open file.\n");
        exit(1);
    }

    getmaxyx(stdscr, h, w);
    getyx(stdscr, ys, xs);


    for(int y = 0; y < h; y++) {  
        
        for(int x = 0; x < w; x++)
        {
            if (' ' != (mvwinch(stdscr, y, x) & A_CHARTEXT))
                lastnospace = x; 
        }

        for(int x = 0; x <= lastnospace; x++)
        {
            putc(mvwinch(stdscr, y, x) & A_CHARTEXT, fd);
        }
        putc('\n', fd);
    }
    fclose(fd);
    wmove(stdscr, ys, xs);
    

    //no work
    /*int h, w, ys, xs;
    int fd;
    if ((fd = open("file.txt",  O_CREAT| O_RDWR ))==-1) {
        printf ("Cannot open file.\n");
        exit(1);
    }

    getmaxyx(stdscr, h, w);
    getyx(stdscr, ys, xs);


    for(int y = 0; y < h; y++) {  
        for(int x = 0; x < w; x++)
        {
            write(fd, mvwinch(stdscr, y, x) & A_CHARTEXT, sizeof(char));
        }
        write(fd, '\n', sizeof(char));
    }
    close(fd);
    wmove(stdscr, ys, xs);
    */
}

int main(int argc, char ** argv)
{
    setlocale(LC_ALL, "");

    initscr();
    signal(SIGWINCH, sig_winch);
    noecho(); // отключение отображения символов, вводимых с клавы
    curs_set(0); // 0-курсор невидимый, любое другое значение -видимый
    Menu();
    keypad(stdscr, TRUE);
    getch();
    clear();
    while(1) {
        InputMode();
        refresh();
    }
}


