#include "BB.h"

extern WINDOW* welcome;
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
    getch();
    delwin(msgbox);
}

void about()
{
    WINDOW* msgbox;
    msgbox = newwin(9,39,8,20);
    box(msgbox,ACS_VLINE, ACS_HLINE);
    wattron(msgbox,A_BOLD);
    mvwprintw(msgbox,1,1,"About us");
    mvwprintw(msgbox,4,2,"Engine: ");
    mvwprintw(msgbox,5,2,"    UI: ");
    wattroff(msgbox,A_BOLD);
    mvwprintw(msgbox,4,11,"SJY / HJS / YTH");
    mvwprintw(msgbox,5,11,"KYH");
    wrefresh(msgbox);
    wgetch(msgbox);
    delwin(msgbox);
    wclear(welcome);
}

void title()
{
    int x=13;
    int y=4;
////////////////////////////////////////////// B
	mvwaddch(welcome,y,x,ACS_CKBOARD);
	mvwaddch(welcome,y,x+1,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+2,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+1,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+2,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+1,ACS_CKBOARD);
////////////////////////////////////////////// R
	mvwaddch(welcome,y,x+4,ACS_CKBOARD);
	mvwaddch(welcome,y,x+5,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+4,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+6,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+4,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+5,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+4,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+6,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+4,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+6,ACS_CKBOARD);
////////////////////////////////////////////// I
	mvwaddch(welcome,y,x+8,ACS_CKBOARD);
	mvwaddch(welcome,y,x+9,ACS_CKBOARD);
	mvwaddch(welcome,y,x+10,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+9,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+9,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+9,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+8,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+9,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+10,ACS_CKBOARD);
////////////////////////////////////////////// C
	mvwaddch(welcome,y,x+12,ACS_CKBOARD);
	mvwaddch(welcome,y,x+13,ACS_CKBOARD);
	mvwaddch(welcome,y,x+14,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+12,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+12,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+12,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+12,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+13,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+14,ACS_CKBOARD);
////////////////////////////////////////////// K	
    mvwaddch(welcome,y,x+16,ACS_CKBOARD);
	mvwaddch(welcome,y,x+19,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+16,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+18,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+16,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+17,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+16,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+18,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+16,ACS_CKBOARD);
    mvwaddch(welcome,y+4,x+19,ACS_CKBOARD);
/////////////////////////////////////////////////////////////////
////////////////////////////////////////////// B
    mvwaddch(welcome,y,x+25,ACS_CKBOARD); //-4
	mvwaddch(welcome,y,x+26,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+25,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+27,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+25,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+26,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+25,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+27,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+25,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+26,ACS_CKBOARD);
////////////////////////////////////////////// R
    mvwaddch(welcome,y,x+29,ACS_CKBOARD);
	mvwaddch(welcome,y,x+30,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+29,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+31,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+29,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+30,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+29,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+31,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+29,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+31,ACS_CKBOARD);
////////////////////////////////////////////// E
    mvwaddch(welcome,y,x+33,ACS_CKBOARD);
	mvwaddch(welcome,y,x+34,ACS_CKBOARD);
	mvwaddch(welcome,y,x+35,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+33,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+33,ACS_CKBOARD);
    mvwaddch(welcome,y+2,x+34,ACS_CKBOARD);
    mvwaddch(welcome,y+2,x+35,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+33,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+33,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+34,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+35,ACS_CKBOARD);
////////////////////////////////////////////// A
    mvwaddch(welcome,y,x+37,ACS_CKBOARD);
	mvwaddch(welcome,y,x+38,ACS_CKBOARD);
    mvwaddch(welcome,y,x+39,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+37,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+39,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+37,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+38,ACS_CKBOARD);
    mvwaddch(welcome,y+2,x+39,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+37,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+39,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+37,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+39,ACS_CKBOARD);
    ////////////////////////////////////////////// K	
    mvwaddch(welcome,y,x+41,ACS_CKBOARD); //+32
	mvwaddch(welcome,y,x+44,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+41,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+43,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+41,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+42,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+41,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+43,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+41,ACS_CKBOARD);
    mvwaddch(welcome,y+4,x+44,ACS_CKBOARD);
    mvwaddstr(welcome,y+5,x+46,"Ver 1.0");
    ////////////////////////////////////////////// E
    mvwaddch(welcome,y,x+46,ACS_CKBOARD); //+14
	mvwaddch(welcome,y,x+47,ACS_CKBOARD);
	mvwaddch(welcome,y,x+48,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+46,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+46,ACS_CKBOARD);
    mvwaddch(welcome,y+2,x+47,ACS_CKBOARD);
    mvwaddch(welcome,y+2,x+48,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+46,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+46,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+47,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+48,ACS_CKBOARD);
    ////////////////////////////////////////////// R
    mvwaddch(welcome,y,x+50,ACS_CKBOARD); //+21
	mvwaddch(welcome,y,x+51,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+50,ACS_CKBOARD);
	mvwaddch(welcome,y+1,x+52,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+50,ACS_CKBOARD);
	mvwaddch(welcome,y+2,x+51,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+50,ACS_CKBOARD);
	mvwaddch(welcome,y+3,x+52,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+50,ACS_CKBOARD);
	mvwaddch(welcome,y+4,x+52,ACS_CKBOARD);
    wrefresh(welcome);
}
