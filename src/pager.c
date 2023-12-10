
#include <stdlib.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    int ch, prev, row, col;
    prev = EOF;
    FILE *fp;
    int x, y;

    // Check terminal args
    if (argc != 2)
    {
        printf("Usage: %s filename", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open file
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        perror("Cannot open the file");
        exit(EXIT_FAILURE);
    }

    initscr();                  // initialize ncurses
    getmaxyx(stdscr, row, col); // get number of screen row and column
    while ((ch = fgetc(fp)) != EOF)
    {
        getyx(stdscr, y, x); // get current cursor position
        if (y == (row - 1))
        {
            printw("<-Press Any Key->"); // print message under the screen
            getch();                     // wait user press a key
            clear();                     // clear the screen
            move(0, 0);                  // move cursor to topper right
        }
        if (prev == '/' && ch == '/')
        {
            attron(A_BOLD);          // start bold attribute
            getyx(stdscr, y, x);     // get current cursor position
            move(y, x - 1);          // move cursor before comment starts
            printw("%c%c", '/', ch); // print comment
        }
        else
            printw("%c", ch); // print char

        refresh(); // refresh screen
        if (ch == '\n')
            attroff(A_BOLD); // turn off bold attribute

        prev = ch;
    }

    endwin();   // 结束 ncurses 库
    fclose(fp); // 关闭文件

    return 0; // 返回程序执行成功的标志
}