#include <ncurses.h>

int main(int argc, char *argv[])
{
    initscr();                 // 初始化 ncurses 库，准备使用屏幕
    printw("Hello World !!!"); // 在屏幕上打印 "Hello World !!!"
    refresh();                 // 刷新屏幕，将打印的内容显示出来
    getch();                   // 等待用户按下一个键
    endwin();                  // 结束 ncurses 库的使用，恢复终端的正常模式

    return 0;
}
