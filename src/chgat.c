#include <ncurses.h>

int main(int argc, char *argv[])
{
    initscr();
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    printw("A Big string which I didn't care to type fully ");
    mvchgat(0, 0, -1, A_BLINK, 1, NULL);
    /*
     * First two parameters specify the position at which to start
     * Third parameter number of characters to update. -1 means till
     * end of line
     * Forth parameter is the normal attribute you wanted to give
     * to the charcter
     * Fifth is the color index. It is the index given during init_pair()
     * use 0 if you didn't want color
     * Sixth one is always NULL
     */
    refresh();
    getch();
    endwin();
    return 0;
}