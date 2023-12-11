#include <panel.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    WINDOW *my_wins[3];
    PANEL *my_panels[3];

    int lines = 10, cols = 40, y = 2, x = 4;

    initscr();
    cbreak();
    noecho();

    my_wins[0] = newwin(lines, cols, y, x);
    my_wins[1] = newwin(lines, cols, y + 1, x + 5);
    my_wins[2] = newwin(lines, cols, y + 2, x + 10);

    for (int i = 0; i < 3; ++i)
        box(my_wins[i], 0, 0);

    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);

    /* Update the stacking order. 2nd panel will be on top */
    update_panels();
    /* Show it on the screen */
    doupdate();

    getch();
    endwin();

    return 0;
}