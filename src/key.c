#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

#define WIDTH 30
#define HEIGHT 10

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main(int argc, char *argv[])
{
    WINDOW *menu_win;
    int highlight = 1, choice = 0, c;

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    int mWidth, mHeight;
    getmaxyx(stdscr, mHeight, mWidth);
    int startx = (mWidth - WIDTH) / 2;
    int starty = (mHeight - HEIGHT) / 2;
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight);
    while (true)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight == 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        default:
            mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);
            refresh();
            break;
        }
        print_menu(menu_win, highlight);
        if (choice != 0)
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);

    clrtoeol();
    refresh();
    endwin();

    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1)
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}