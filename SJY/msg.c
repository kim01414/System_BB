#include <ncurses.h>
#include "BB.h"

void popup(char* msg, int space,int flag)
{
    int settings = A_NORMAL;
    WINDOW *msgbox;
    settings |= flag;
    msgbox = newwin(9,39,8,12);
    BOX(msgbox,39,9,COLOR_PAIR(1));
    wattron(msgbox,settings);
    mvwprintw(msgbox,4,8+space,msg);
    wrefresh(msgbox);
    getch();
    wrefresh(msgbox);
    delwin(msgbox);
}

void gameover(int score,int hscore)
{
    WINDOW *msgbox;
    msgbox = newwin(9,39,8,12);
    BOX(msgbox,39,9,COLOR_PAIR(1));
    wattron(msgbox,A_BOLD);
    mvwprintw(msgbox,4,14,"GAME OVER");
    wattroff(msgbox,A_BOLD);
    wrefresh(msgbox);
    wgetch(msgbox);
    delwin(msgbox);
}
