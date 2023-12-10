#include <ncurses.h>

#define _DEBUG

typedef struct _win_boarder_struct
{
    chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct
{
    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int main(int argc, char *argv[])
{
    WIN win;
    int ch;

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    printw("Press F2/q to exit");
    refresh();
    attroff(COLOR_PAIR(1));

    init_win_params(&win);

    create_box(&win, TRUE);
    while ((ch = getch()) != KEY_F(2) && ch != 'q')
    {
        create_box(&win, FALSE);
        switch (ch)
        {
        case KEY_LEFT:
            --win.startx;
            break;
        case KEY_RIGHT:
            ++win.startx;
            break;
        case KEY_UP:
            --win.starty;
            break;
        case KEY_DOWN:
            ++win.starty;
            break;
        case 'r':
            win.startx = (COLS - win.width) / 2;
            win.starty = (LINES - win.height) / 2;
            break;
        case '+':
            ++win.height, ++win.width;
            break;
        case '-':
            if (win.height > 0)
                --win.height;
            if (win.width > 0)
                --win.width;
            break;
        }
        create_box(&win, TRUE);
        print_win_params(&win);
    }
    endwin();
    return 0;
}

void init_win_params(WIN *p_win)
{
    p_win->height = 3;
    p_win->width = 10;
    p_win->starty = (LINES - p_win->height) / 2;
    p_win->startx = (COLS - p_win->width) / 2;
    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';
}

void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
    mvprintw(25, 0, "x: %d, y: %d, w: %d, h: %d", p_win->startx, p_win->starty, p_win->width, p_win->height);
#endif
}

void create_box(WIN *p_win, bool flag)
{
    int i, j;
    int x, y, w, h;
    x = p_win->startx;
    y = p_win->starty;
    w = p_win->width;
    h = p_win->height;

    if (flag == TRUE)
    {
        mvaddch(y, x, p_win->border.tl);
        mvaddch(y, x + w, p_win->border.tr);
        mvaddch(y + h, x, p_win->border.bl);
        mvaddch(y + h, x + w, p_win->border.br);
        mvhline(y, x + 1, p_win->border.ts, w - 1);
        mvhline(y + h, x + 1, p_win->border.bs, w - 1);
        mvvline(y + 1, x, p_win->border.ls, h - 1);
        mvvline(y + 1, x + w, p_win->border.rs, h - 1);
    }
    else
        for (j = y; j <= y + h; ++j)
            for (i = x; i <= x + w; ++i)
                mvaddch(j, i, ' ');
    refresh();
}