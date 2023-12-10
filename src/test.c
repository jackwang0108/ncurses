/**
 * @file main.c
 * @author Jack Wang (jack3shihong@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-12-09
 *
 * @copyright Copyright Shihong Wang (c) 2023 with GNU Public License V3.0
 *
 */
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    WINDOW *win = initscr();
    raw();
    // noecho();
    int prevStatus = curs_set(0);

    char *ptr = "Hello, %s! PrevStatus: %d";

    mvprintw(LINES / 2, (COLS - strlen(ptr)) / 2, ptr, "Jack Wang", prevStatus);
    // refresh();

    char ch;
    while ((ch = getch()) != 'q')
        ;
    endwin();

    return 0;
}