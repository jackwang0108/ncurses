#include <string.h>
#include <ncurses.h>

int main(int argc, char *argv[])
{
    char msg[] = "Enter a string: "; // 定义一个字符串变量 msg，用于提示用户输入字符串
    char str[80];                    // 定义一个字符数组变量 str，用于存储用户输入的字符串
    int row, col;                    // 定义两个整型变量 row 和 col，用于存储屏幕的行数和列数

    WINDOW *win = initscr();                               // 初始化 ncurses 库，创建一个新的窗口，并将其地址赋值给 win 变量
    getmaxyx(stdscr, row, col);                            // 获取屏幕的行数和列数，并将其分别赋值给 row 和 col 变量
    mvprintw(row / 2, (col - strlen(msg)) / 2, "%s", msg); // 在屏幕上打印提示信息 msg，使其居中显示在屏幕的一半位置
    getstr(str);                                           // 从用户输入中获取一个字符串，并将其存储在 str 变量中
    mvprintw(LINES - 2, 0, "You entered: %s", str);        // 在屏幕上打印用户输入的字符串
    getch();                                               // 等待用户按下一个键
    endwin();                                              // 结束 ncurses 库，关闭窗口

    return 0; // 返回程序执行成功的标志
}
