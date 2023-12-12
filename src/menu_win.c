#include <menu.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 4

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
    (char *)NULL,
};

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main()
{
    /* Initialize curses */
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);

    /* Create items */
    int n_choices = ARRAY_SIZE(choices);
    ITEM **my_items = (ITEM **)calloc(sizeof(ITEM *), n_choices);
    for (int i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i], choices[i]);

    /* Crate menu */
    MENU *my_menu = new_menu((ITEM **)my_items);

    /* Create the window to be associated with the menu */
    MENU *my_menu_win = (MENU *)newwin(10, 40, 4, 4);
    keypad((WINDOW *)my_menu_win, TRUE);

    /* Set main window and sub window */
    set_menu_win(my_menu, (WINDOW *)my_menu_win);
    set_menu_sub(my_menu, derwin((WINDOW *)my_menu_win, 6, 38, 3, 2));

    /* Set menu mark to the string " * " */
    set_menu_mark(my_menu, " * ");

    /* Print a border around the main window and print a title */
    box((WINDOW *)my_menu_win, 0, 0);
    print_in_middle((WINDOW *)my_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
    mvwaddch((WINDOW *)my_menu_win, 2, 0, ACS_LTEE);
    mvwhline((WINDOW *)my_menu_win, 2, 1, ACS_HLINE, 38);
    mvwaddch((WINDOW *)my_menu_win, 2, 39, ACS_RTEE);
    mvprintw(LINES - 2, 0, "F2 to exit");
    refresh();

    /* Post the menu */
    post_menu(my_menu);
    wrefresh((WINDOW *)my_menu_win);

    int c;
    while ((c = wgetch((WINDOW *)my_menu_win)) != KEY_F(2))
    {
        switch (c)
        {
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        }
        wrefresh((WINDOW *)my_menu_win);
    }

    /* Unpost and free all the memory taken up */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (int i = 0; i < n_choices; ++i)
        free_item(my_items[i]);
    endwin();
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    int x, y;

    if (win == NULL)
        win = stdscr;
    getyx(win, y, x);
    if (startx != 0)
        x = startx;
    if (starty != 0)
        y = starty;
    if (width == 0)
        width = 80;

    int length = strlen(string);
    float temp = (float)(width - length) / 2;
    x = startx + (int)temp;
    wattron(win, color);
    mvwprintw(win, y, x, "%s", string);
    wattroff(win, color);
    refresh();
}