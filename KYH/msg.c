#include <ncurses.h>
#include "BB.h"

void popup(char* msg, int space,int flag)
{
    int settings = A_NORMAL;
    WINDOW *msgbox;
    settings |= flag;
    msgbox = newwin(9,39,7,11);
    box(msgbox,ACS_VLINE,ACS_HLINE);
    wattron(msgbox,settings);
    mvwprintw(msgbox,4,8+space,msg);
    wrefresh(msgbox);
    getch();
    wclear(msgbox);
    wrefresh(msgbox);
    delwin(msgbox);
    refresh();
}

void Error(char* msg)
{
    
}