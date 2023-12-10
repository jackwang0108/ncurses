#include <string.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    char msg[] = "Just a String"; // 定义一个字符数组并初始化为 "Just a String"
    int row, col;                 // 定义两个整型变量用于存储行数和列数

    WINDOW *win = initscr();                                                           // 初始化 ncurses 库，准备使用屏幕，并返回一个指向窗口的指针
    getmaxyx(stdscr, row, col);                                                        // 获取屏幕的行数和列数，并存储到变量 row 和 col 中
    mvprintw(row / 2, col / 2, "%s", msg);                                             // 在屏幕上打印字符串 msg，位于屏幕的中心位置
    mvprintw(row - 2, 0, "This screen has %d rows and %d columns\n", row, col);        // 在屏幕上打印屏幕的行数和列数信息
    printw("Try to resize your window (if possible) and then run this program again"); // 在屏幕上打印提示信息
    refresh();                                                                         // 刷新屏幕，将打印的内容显示出来
    getch();                                                                           // 等待用户按下一个键
    endwin();                                                                          // 结束 ncurses 库的使用，恢复终端的正常模式

    return 0;
}
