#include <string.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    int attr_array[] = {
        A_NORMAL,
        A_STANDOUT,
        A_UNDERLINE,
        A_REVERSE,
        A_BLINK,
        A_DIM,
        A_BOLD,
        A_PROTECT,
        A_INVIS,
    };
    char *attr_names[] = {
        "A_NORMAL",
        "A_STANDOUT",
        "A_UNDERLINE",
        "A_REVERSE",
        "A_BLINK",
        "A_DIM",
        "A_BOLD",
        "A_PROTECT",
        "A_INVIS",
    };
    char *msg = "Test";
    int row, col;

    initscr();
    getmaxyx(stdscr, row, col);
    for (int i = 0; i < sizeof(attr_array) / sizeof(int); i++)
    {
        printw("%s: ", attr_names[i]);
        attron(attr_array[i]);
        printw("%s", msg);
        attroff(attr_array[i]);
        printw("%c", '\n');
        refresh();
    }
    getch();
    endwin();
    return 0;
}