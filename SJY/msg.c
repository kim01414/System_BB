#include "BB.h"

extern int speed;
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

void settings(int* option1 ){
	int spd,opt1=1,opt2=1,i,sel=1;
	char *SPEED[3] = {"  SLOW  ", " NORMAL ", "  FAST  "};
	char *OPT1[3]  = {"  VAL1  ", "  VAL2  ", "  VAL3  "};
	char *OPT2[3]  = {"  VAL1  ", "  VAL2  ", "  VAL3  "};
	WINDOW *msgbox;
	if(speed==SLOW) spd=0;
	else if(speed==NORMAL) spd=1;
	else if(speed==FAST) spd=2;
    msgbox = newwin(9,39,10,20);
    box(msgbox,ACS_VLINE,ACS_HLINE);
	for(i=1 ; i<8 ;i++) mvwaddch(msgbox,i,38,ACS_VLINE|COLOR_PAIR(7));
	for(i=1 ; i<39 ;i++) mvwaddch(msgbox,8,i,ACS_HLINE|COLOR_PAIR(7));
	mvwaddch( msgbox,8,38,ACS_LRCORNER|COLOR_PAIR(7) );
	wattron(msgbox,A_BOLD);
    mvwprintw(msgbox,0,16,"Settings");
	for(i=3;i<6;i++){
		mvwaddch( msgbox,i,17,ACS_LARROW);//|A_STANDOUT);
		mvwaddch( msgbox,i,28,ACS_RARROW);//|A_STANDOUT);
	}
	wattroff(msgbox,A_BOLD);
	mvwprintw(msgbox,3,5,"SPEED  ");
	mvwprintw(msgbox,4,5,"Option1");
	mvwprintw(msgbox,5,5,"Option2");
	keypad(msgbox,TRUE);
	while(1){
		if(sel==1) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,3,19,"%s",SPEED[spd]);
		if(sel==1) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==2) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,4,19,"%s",OPT1[opt1]);
		if(sel==2) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==3) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,5,19,"%s",OPT2[opt2]);
		if(sel==3) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==4) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,7,17," OK ");
		if(sel==4) wattroff(msgbox,A_STANDOUT|A_BOLD);
		wrefresh(msgbox);

		i = wgetch(msgbox);
		if(i==KEY_UP){
			sel--;
			if(sel<1) sel=4;
		}
		else if(i==KEY_DOWN){
			sel++;
			if(sel>4) sel=1;
		}
		else if(i==KEY_LEFT){
			if(sel==1 && spd>0 ) spd--;
			else if(sel==2 && opt1>0 ) opt1--;
			else if(sel==3 && opt2>0 ) opt2--;
		}
		else if(i==KEY_RIGHT){
			if(sel==1 && spd<2 ) spd++;
			else if(sel==2 && opt1<2 ) opt1++;
			else if(sel==3 && opt2<2 ) opt2++;
		}
		else if(i=='\n' && sel==4){
			break;
		}
	}
	
	if(spd==0) speed = SLOW;
	else if(spd==1) speed = NORMAL;
	else if(spd==2) speed = FAST;

    delwin(msgbox);
}

void about()
{
	int i;
    WINDOW* msgbox;
    msgbox = newwin(9,39,10,20);
	box(msgbox,ACS_VLINE,ACS_HLINE);
	for(i=1 ; i<8 ;i++) mvwaddch(msgbox,i,38,ACS_VLINE|COLOR_PAIR(7));
	for(i=1 ; i<39 ;i++) mvwaddch(msgbox,8,i,ACS_HLINE|COLOR_PAIR(7));
	mvwaddch( msgbox,8,38,ACS_LRCORNER|COLOR_PAIR(7) );

    wattron(msgbox,A_BOLD);
    mvwprintw(msgbox,0,14,"About us");
    mvwprintw(msgbox,3,2,"Engine: ");
    mvwprintw(msgbox,4,2,"    UI: ");
	
    wattroff(msgbox,A_BOLD);
	mvwprintw(msgbox,5,1,"https://github.com/kim01414/System_BB");
    mvwprintw(msgbox,3,11,"SJY / HJS / YTH");
    mvwprintw(msgbox,4,11,"KYH");
    wrefresh(msgbox);
    wgetch(msgbox);
    delwin(msgbox);
    wclear(welcome);
}

void title()
{
	int i;
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
	mvwaddstr(welcome,y+5,x+46,"Ver 0.1");
	for(i=32 ; i<46 ; i++){
		mvwaddch(welcome,13,i,ACS_HLINE);
		mvwaddch(welcome,18,i,ACS_HLINE|COLOR_PAIR(7));
	}
	for(i=13 ; i<19; i++){
		mvwaddch(welcome,i,32,ACS_VLINE);
		mvwaddch(welcome,i,45,ACS_VLINE|COLOR_PAIR(7));
	} 
	mvwaddch(welcome,13,32,ACS_ULCORNER);
	mvwaddch(welcome,18,32,ACS_LLCORNER);
	mvwaddch(welcome,13,45,ACS_URCORNER|COLOR_PAIR(7));
	mvwaddch(welcome,18,45,ACS_LRCORNER|COLOR_PAIR(7));
    wrefresh(welcome);
}