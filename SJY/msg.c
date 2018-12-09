#include <ncurses.h>
#include "BB.h"

void popup(char* msg, int space,int flag)
{
    int settings = A_NORMAL;
    WINDOW *msgbox;
    settings |= flag;
    msgbox = newwin(9,39,10,20);
    BOX(msgbox,39,9,COLOR_PAIR(1));
    wattron(msgbox,settings);
    mvwprintw(msgbox,4,8+space,msg);
    wrefresh(msgbox);
    getch();
    wrefresh(msgbox);
    delwin(msgbox);
    refresh();
}

void gameover(int score,int hscore)
{
    int color = COLOR_PAIR(1);
    WINDOW *msgbox;
    //keypad(stdscr,FALSE);
    msgbox = newwin(9,39,10,20);
    BOX(msgbox,39,9,COLOR_PAIR(1));
    wattron(msgbox,A_BOLD);
    mvwprintw(msgbox,4,14,"GAME OVER");
    wattroff(msgbox,A_BOLD);
    //mvwprintw(msgbox,4,11, "BEST Score: %2d",hscore);
    //mvwprintw(msgbox,5,11, "Your Score: %2d",score);
    wrefresh(msgbox);
    getch();
    //delwin(msgbox);
    echo();
	endwin();
	exit(1);
}
