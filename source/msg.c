#include "BB.h"

extern int speed;
extern WINDOW* welcome;
void popup(char* msg, int space,int flag)
{
    int settings = A_NORMAL;
	extern int lock;
    WINDOW *msgbox;
	lock=1;
    settings |= flag;
    msgbox = newwin(9,39,8,12);
    BOX(msgbox,39,9,COLOR_PAIR(1));
    wattron(msgbox,settings);
    mvwprintw(msgbox,4,8+space,msg);
    wrefresh(msgbox);
    getch();
    delwin(msgbox);
	lock=0;
}

int hold(){
	WINDOW *msgbox;
	int temp;
	extern int test_time;
    msgbox = newwin(9,39,8,12);
    BOX(msgbox,39,9,COLOR_PAIR(1));
	test_time=-1;
    wattron(msgbox,A_BOLD);
	mvwprintw(msgbox,4,14,"GAME PAUSED");
    wrefresh(msgbox);
    getch();
	test_time=temp;
    delwin(msgbox);
}

void Select(){
	extern int maplevel;
	int i,sel=1,mapsel=0, spd;
	char* map[4] =   {"        MAP01        ","        MAP02        ","        MAP03        ","        MAP04        "};
	char *SPEED[3] = {"        SLOW         ","        NORMAL       ","        FAST         "};
	WINDOW *msgbox = newwin(9,39,11,20);
	if(speed==SLOW) spd=0;
	else if(speed==NORMAL) spd=1;
	else if(speed==FAST) spd=2;
	box(msgbox,ACS_VLINE,ACS_HLINE);
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	for(i=1 ; i<8 ;i++) mvwaddch(msgbox,i,38,ACS_VLINE|COLOR_PAIR(7));
	for(i=1 ; i<39 ;i++) mvwaddch(msgbox,8,i,ACS_HLINE|COLOR_PAIR(7));
	mvwaddch( msgbox,8,38,ACS_LRCORNER|COLOR_PAIR(7) );
	wattron(msgbox,A_BOLD);
	
	mvwaddch( msgbox,3,10,ACS_LARROW);
	mvwaddch( msgbox,3,34,ACS_RARROW);
	mvwaddch( msgbox,5,10,ACS_LARROW);
	mvwaddch( msgbox,5,34,ACS_RARROW);
	wattron(msgbox,COLOR_PAIR(1));
	mvwprintw(msgbox,0,14,"Select MAP");
	mvwprintw(msgbox,3,3,"MAP ");
	mvwprintw(msgbox,5,3,"SPEED ");
	wattroff(msgbox,A_BOLD|COLOR_PAIR(1));
	keypad(msgbox,TRUE);
	while(1){
		if(sel==1) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,3,12,"%s",map[mapsel]);
		if(sel==1) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==2) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,5,12,"%s",SPEED[spd]);
		if(sel==2) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==3) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,7,8," Start ");
		if(sel==3) wattroff(msgbox,A_STANDOUT|A_BOLD);

		if(sel==4) wattron(msgbox,A_STANDOUT|A_BOLD);
			mvwprintw(msgbox,7,23," Cancel ");
		if(sel==4) wattroff(msgbox,A_STANDOUT|A_BOLD);
		
		wrefresh(msgbox);

		i = wgetch(msgbox);
		if(i==KEY_UP){
			if(sel>2) sel=2;
			else sel=1;
		}
		else if(i==KEY_DOWN && sel<4){
			sel++;
		}
		else if(i==KEY_LEFT){
			if (sel==1 && mapsel>0) mapsel--; 
			else if(sel==2 && spd>0) spd--;
			else if(sel==4) sel=3;
		}
		else if(i==KEY_RIGHT){
			if(sel==1 && mapsel<3 ) mapsel++;
			else if(sel==2 && spd<2) spd++;
			else if(sel==3) sel=4;
		}
		else if(i=='\n'){
			if(sel==4) maplevel=-1;
			else maplevel=mapsel+1;
			break;
		}
	}	
	if(spd==0) speed = SLOW;
	else if(spd==1) speed = NORMAL;
	else if(spd==2) speed = FAST;
	delwin(msgbox);
}

void help()
{
    int i,j;
    WINDOW* msgbox;
    msgbox = newwin(14,39,8,20);
	init_pair(1,COLOR_BLUE,COLOR_BLACK); //Fonts and Brick1
	init_pair(2,COLOR_GREEN,COLOR_BLACK); //Brick2
	init_pair(3,COLOR_CYAN,COLOR_BLACK); //Brick3
	init_pair(4,COLOR_RED,COLOR_BLACK); //Explosive
	init_pair(5,COLOR_WHITE,COLOR_BLACK); //Invisible

	box(msgbox,ACS_VLINE,ACS_HLINE);
	for(i=1 ; i<14 ;i++) mvwaddch(msgbox,i,38,ACS_VLINE|COLOR_PAIR(7));
	for(i=1 ; i<39 ;i++) mvwaddch(msgbox,13,i,ACS_HLINE|COLOR_PAIR(7));
	mvwaddch( msgbox,13,38,ACS_LRCORNER|COLOR_PAIR(7));
	wattron(msgbox,A_BOLD|COLOR_PAIR(1));
    mvwprintw(msgbox,0,17,"Help");
    mvwprintw(msgbox,1,2,"-Controls-");
	mvwprintw(msgbox,6,2,"-Bricks-");
    wattroff(msgbox,COLOR_PAIR(1));
	mvwprintw(msgbox,2,2,"Move left");
    mvwprintw(msgbox,3,2,"Move right");
	mvwprintw(msgbox,4,2,"Pause game");
	mvwprintw(msgbox,7,2,"Normal Brick(+0)");
	mvwprintw(msgbox,8,2,"Normal Brick(+1)");
	mvwprintw(msgbox,9,2,"Normal Brick(+2)");
    mvwprintw(msgbox,10,2,"Explosive Brick");
	mvwprintw(msgbox,11,2,"Invisible Brick");
	wattroff(msgbox,A_BOLD);
	mvwprintw(msgbox,2,25,"Left Key");
	mvwprintw(msgbox,3,25,"Right Key");
	mvwprintw(msgbox,4,25,"Enter");

	for(i=7; i<12 ;i++){
		for(j=25 ; j<28 ;j++ ){
			mvwaddch(msgbox,i,j+2,ACS_CKBOARD|COLOR_PAIR(i-6));
		}
	}
    wrefresh(msgbox);
    wgetch(msgbox);
    delwin(msgbox);
    wclear(welcome);
}

void about()
{
	int i;
    WINDOW* msgbox;
    msgbox = newwin(9,41,11,20);
	box(msgbox,ACS_VLINE,ACS_HLINE);
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	for(i=1 ; i<8 ;i++) mvwaddch(msgbox,i,40,ACS_VLINE|COLOR_PAIR(7));
	for(i=1 ; i<41 ;i++) mvwaddch(msgbox,8,i,ACS_HLINE|COLOR_PAIR(7));
	mvwaddch( msgbox,8,40,ACS_LRCORNER|COLOR_PAIR(7) );

    wattron(msgbox,A_BOLD|COLOR_PAIR(1));
    mvwprintw(msgbox,0,15,"About us");
    mvwprintw(msgbox,3,2,"Engine: ");
    mvwprintw(msgbox,4,2,"    UI: ");
	
    wattroff(msgbox,A_BOLD|COLOR_PAIR(1));
	mvwprintw(msgbox,5,2,"https://github.com/kim01414/System_BB");
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
	init_color(COLOR_MAGENTA,105,105,105);
	init_pair(1,COLOR_MAGENTA,COLOR_BLACK);
	for(i=31 ; i<47 ; i++){
		mvwaddch(welcome,13,i,ACS_HLINE);
		mvwaddch(welcome,18,i,ACS_HLINE|COLOR_PAIR(1));
	}
	for(i=13 ; i<19; i++){
		mvwaddch(welcome,i,31,ACS_VLINE);
		mvwaddch(welcome,i,46,ACS_VLINE|COLOR_PAIR(1));
	} 
	mvwaddch(welcome,13,31,ACS_ULCORNER);
	mvwaddch(welcome,18,31,ACS_LLCORNER);
	mvwaddch(welcome,13,46,ACS_URCORNER|COLOR_PAIR(1));
	mvwaddch(welcome,18,46,ACS_LRCORNER|COLOR_PAIR(1));
    wrefresh(welcome);
}
