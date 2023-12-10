#include <ncurses.h>

int main(int argc, char *argv[])
{
    initscr();                                                    // 初始化 ncurses 库，准备使用屏幕
    raw();                                                        // 设置终端为原始模式，禁用行缓冲和回显
    keypad(stdscr, TRUE);                                         // 启用键盘的特殊键（如函数键、方向键等）
    noecho();                                                     // 禁止输入字符的回显
    printw("Type any character to see it in bold (q to quit)\n"); // 在屏幕上打印提示信息

    int ch;
    while ((ch = getch()) != 'q') // 循环读取用户输入的字符，直到输入字符为 'q'
    {
        if (ch == KEY_F(1))           // 如果用户按下了 F1 键
            printw("F1 Key Pressed"); // 在屏幕上打印 F1 Key Pressed
        else
        {
            printw("The pressed key is "); // 在屏幕上打印 The pressed key is
            attron(A_BOLD);                // 开启字符加粗属性
            printw("%c\n", ch);            // 在屏幕上打印用户输入的字符，并换行
            attroff(A_BOLD);               // 关闭字符加粗属性
        }
    }

    refresh(); // 刷新屏幕，将打印的内容显示出来
    getch();   // 等待用户按下一个键
    endwin();  // 结束 ncurses 库的使用，恢复终端的正常模式

    return 0;
}