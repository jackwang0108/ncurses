#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define NITEM 10

#define BASE_STR "Choice"
#define EXIT_STR "Exit"

int main(int argc, char *argv[])
{
    // Initialize the meny
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // Make Menu Strings
    char **menuStrings = (char **)calloc(sizeof(char *), NITEM);
    for (int i = 0; i < NITEM; i++)
    {
        menuStrings[i] = (char *)calloc(sizeof(char), strlen(BASE_STR) + 4);
        sprintf(menuStrings[i], "%s %d", BASE_STR, i);
    }

    // Make Menu Items
    char **stringNums = (char **)calloc(sizeof(char *), NITEM);
    ITEM **menuItems = (ITEM **)calloc(sizeof(ITEM *), NITEM);
    for (int i = 0; i < NITEM; i++)
    {
        stringNums[i] = (char *)calloc(sizeof(char), 4);
        sprintf(stringNums[i], "%3d", i + 1);
        menuItems[i] = new_item(stringNums[i], i == NITEM - 1 ? EXIT_STR : menuStrings[i]);
    }

    // Make Menu
    MENU *myMenu = new_menu(menuItems);
    mvprintw(LINES - 2, 0, "F2 to Exit");
    post_menu(myMenu);
    refresh();

    int ch;
    int choice = 0;
    while ((ch = getch()) != KEY_F(2))
    {
        switch (ch)
        {
        case KEY_DOWN:
            choice = (NITEM + choice + 1) % NITEM;
            menu_driver(myMenu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            choice = (NITEM + choice - 1) % NITEM;
            menu_driver(myMenu, REQ_UP_ITEM);
            break;
        case 'l':
            menu_driver(myMenu, REQ_LAST_ITEM);
            break;
        case 27:
            goto end;
            break;
        case '\n':
            if (choice == 9)
                goto end;
            break;
        }
    }
end:
    for (int i = 0; i < NITEM; i++)
    {
        free_item(menuItems[i]);
        free(stringNums[i]);
        free(menuStrings[i]);
    }
    free_menu(myMenu);
    free(stringNums);
    free(menuItems);
    free(menuStrings);
    return 0;
}