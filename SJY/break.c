#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>
#include "BB.h"

int map[MAP_HEIGHT][MAP_WIDTH];
int current_board;
int current_ballX, current_ballY;
int dx=-1, dy=-1;		//ball delta
int brick_left=0;
int test_stage=1, test_score=0, test_time=0, test_high;

WINDOW *gamebox, *scorebox;

int main(){
	int h, w; 		//height and width variables for loop
	int q=1, c=1;	//don't care variables..? not quite importent things
	char ch;

	//to make ball thread
	pthread_t ballThread, TimeThread;
	int thr_id;
	int status;


	/*	Initialize	*/
	highscore(0);
	initialize();

	thr_id = pthread_create(&ballThread, NULL, ballThreadFunc, (void*)&c);
	thr_id = pthread_create(&TimeThread, NULL, stopwatch, NULL);
	while(test_time!=-1){
		c=wgetch(stdscr);	//if user input arrow key
		setBoard(c);		//handle arrow key
		refreshMap();		//loop continue
	}
	endwin();	//end curses
	return 0;
}

void test1(){
	int i, j;

	for(i=4; i<BRICK_HEIGHT; i+=2) {
		for(j=7; j<8; j++){
			map[i][j]=BRICK3;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=8; j<9; j++) {
			map[i][j]=BRICK2;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=9; j<10; j++) {
			map[i][j]=BRICK1;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=10; j<11; j++) {
			map[i][j]=BRICKE;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=11; j<12; j++) {
			map[i][j]=BRICKU;
			brick_left+=2;
			if(j%4==1) j++;
		}
	}
}

void refreshMap(){ /////////// █ ░ ▒ ▓
	int h, w;
	mvwprintw(scorebox,2,7,"%3d",test_stage);
	mvwprintw(scorebox,2,29,"%7d",test_high);
	mvwprintw(scorebox,2,40,"%7d",test_score);
	mvwprintw(scorebox,2,53,"%4d",test_time);
	for(h=0; h<MAP_HEIGHT; h++){
		for(w=0; w<MAP_WIDTH; w++){
			wmove(gamebox,h,w);
			if(map[h][w]==EMPTY){
				waddch(gamebox,' ');
			}
			else if(map[h][w]==BOARD){
				waddch(gamebox,ACS_CKBOARD);
			}
			else if(map[h][w]==BALL){
				waddch(gamebox,'O'|A_BOLD);
			}
			else if(map[h][w]==BRICK3){
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(2));
			}
			else if(map[h][w]==BRICK2) {
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(4));
			}
			else if(map[h][w]==BRICK1) {
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(5));
			}
		}
	}
	wrefresh(gamebox);
	wrefresh(scorebox);
}

void setBoard(int c){
	int i, sth;

	switch(c){
		case KEY_LEFT:
			sth = map[BOARD_HEIGHT][current_board-1];	//check left
			if(sth==0){		//empty left
				moveBoard(-1);
			}else if(sth==1){;}// there is wall, don't move
			break;
		case KEY_RIGHT:
			sth = map[BOARD_HEIGHT][current_board+8];	//check right
			if(sth==0){
				moveBoard(1);
			}else if(sth==1){;}
			break;
		case 114:
		case 82:
			wrefresh(scorebox);
			wrefresh(gamebox);
			refreshMap();
			break;
	}
}


void moveBoard(int d){
	int i;


	if(d==-1){
		map[BOARD_HEIGHT][current_board+7]=EMPTY;	//set rightend to empty
		map[BOARD_HEIGHT][--current_board]=BOARD;	//set leftend to board
	}else if(d==1){
		map[BOARD_HEIGHT][current_board]=EMPTY;
		map[BOARD_HEIGHT][++current_board+7]=BOARD;
	}
}

void *ballThreadFunc(void* data){
	while(test_time!=-1){
		setBallPos();
	}
}

void* stopwatch(){
	while(test_time!=-1){
		test_time++;
		sleep(1);
	}
}

void setBallPos(){
	int temp;
	temp = map[current_ballX+dx][current_ballY+dy];
	switch(temp){
		case WALL:	//when next pos is wall, bounce
			setBallDel(0);
			break;
		case BOARD:		//when next pos is board, bounce
			setBallDel(0);
			break;
		case BRICK3:		//when next pos is brick, break the brick and bounce
		case BRICK2:
		case BRICK1:
			setBallDel(temp);
			test_score+=100;
			if(test_score>=test_high) test_high=test_score; 
			break;
		case WALL_BOTTOM:	//when next pos is bottom, game end
			highscore(1);
			test_time=-1;
			gameover(test_score,test_high);
			echo();
			endwin();
			exit(1);
			break;
	}


	//make prev ball to empty
	map[current_ballX][current_ballY]=EMPTY;
	//set new position
	current_ballX+=dx;
	current_ballY+=dy;
	map[current_ballX][current_ballY]=BALL;

	refreshMap();
	usleep(200000);
}


void setBallDel(int what){
	if(map[current_ballX][current_ballY-1]!=EMPTY){
		//if left is not empty
		dy=1;
		deleteBrick(what, 0,-1);
	}else if(map[current_ballX][current_ballY+1]!=EMPTY){
		//if right is not empty
		dy=-1;
		deleteBrick(what, 0, 1);
	}else if(map[current_ballX-1][current_ballY]!=EMPTY){
		//if up is not empty
		dx=1;
		deleteBrick(what, -1, 0);
	}else if(map[current_ballX+1][current_ballY]!=EMPTY){
		//if down is not empty
		dx=-1;
		deleteBrick(what, 1, 0);
	}else if(map[current_ballX-1][current_ballY-1]!=EMPTY){
		//if top left corner is not empty
		//this may be work if ball collide at the corner of bricks or board
		dx=1; dy=1;
		deleteBrick(what, -1, -1);
	}else if(map[current_ballX-1][current_ballY+1]!=EMPTY){
		//if top right corner is not empty
		dx=1; dy=-1;
		deleteBrick(what, -1, 1);
	}else if(map[current_ballX+1][current_ballY-1]!=EMPTY){
		//if bottom left corner is not empty
		dx=-1; dy=1;
		deleteBrick(what, 1, -1);
	}else if(map[current_ballX+1][current_ballY+1]!=EMPTY){
		//if bottom right corner is not empty
		dx=-1; dy=-1;
		deleteBrick(what, 1, 1);
	}
}


void makebrick(){
	int i, j;

	for(i=4; i<BRICK_HEIGHT; i+=2){
		for(j=7; j<MAP_WIDTH-7; j++){
			map[i][j]=BRICK3;
			brick_left+=2;
			if(j%4==1) j++;
		}
	}
}

void deleteBrick(int what, int x, int y)
{
	int xpos = current_ballX+x, ypos = current_ballY+y;
	int temp = ypos;

	// 1. normal bricks control.
	if(what == BRICK3 || what == BRICK2 || what == BRICK1) {
		map[xpos][ypos]--;
		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp]--;
		} // for left bricks

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp]--;
		} // for right bricks

		brick_left--;
		// bricks counter.
	}

	// 2. explosive bricks control.
	/* left hit, -1 left bricks. right hit, -1 right bricks.
	   top and bottom hit, remove top bottom bricks.
	   using recursive call.	             	       */
	else if(what == BRICKE) {
		map[xpos][ypos] = 0;

		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp] = 0;
		{

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp] = 0;
		}
		brick_left--; // bricks counter.

		//explosive function.
		if(map[xpos][ypos-2] != EMPTY || map[xpos][ypos-2] != WALL) {
			deletebrick(map[xpos][ypos-2] ,xpos, ypos-2);
		} // left

		else if(map[xpos][ypos+2] != EMPTY || map[xpos][ypos+2] != WALL) {
			deletebrick(map[xpos][ypos+2] ,xpos, ypos+2);
		} // right

		else if (map[xpos+1][ypos] != EMPTY || map[xpos+1][ypos] != WALL) {
			deletebrick(map[xpos+1][ypos], xpos+1, ypos);
			deletebrick(map[xpos-1][ypos], xpos-1, ypos);
		} // top and bottom.

		else if (map[xpos-1][ypos] != EMPTY || map[xpos-1][ypos] != WALL) {
			deletebrick(map[xpos+1][ypos], xpos+1, ypos);
			deletebrick(map[xpos-1][ypos], xpos-1, ypos);
		} // top and bottom.

	} // left brick remove.


	// 3. invisible bricks control.
	else if(what == BRICKU) {
		map[xpos][ypos] = 1;
		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp] = 1;
		} // make it level one block. left

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp] = 1;
		} // right

		brick_left--;
                // bricks counter.
	}

}

void BOX(WINDOW* win, int X,int Y, int color){
	box(win,ACS_VLINE|color,ACS_HLINE|color);
	mvwaddch(win, 0,0       ,ACS_ULCORNER|color);
    mvwaddch(win, 0,X-1    ,ACS_URCORNER|color);
    mvwaddch(win, Y-1,0    ,ACS_LLCORNER|color);
    mvwaddch(win, Y-1,X-1 ,ACS_LRCORNER|color);
}

void initialize() //80 x 26
{
	int h, w;
	char ch;
	//setlocale(LC_ALL, "ko_KR.utf8");
	//setlocale(LC_CTYPE, "ko_KR.utf8");
	initscr();
	start_color();
	clear();		//initialise screen
	curs_set(0);	//make user can't see the cursor
	noecho();
	keypad(stdscr, TRUE);	//enables the reading of func keys(arrow keys)
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_RED,COLOR_WHITE);
	init_pair(3,COLOR_WHITE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_WHITE);
	init_pair(5,COLOR_GREEN,COLOR_WHITE);
	gamebox = newwin(22,62,4,9);
	scorebox = newwin(4,62,0,9);
	wattron(gamebox,COLOR_PAIR(1));
	BOX(gamebox,62,22,COLOR_PAIR(3));
	BOX(scorebox,62,4,COLOR_PAIR(3));
	refresh();
	wattron(scorebox,A_BOLD);
	mvwprintw(scorebox,1,5, "STAGE");
	mvwprintw(scorebox,1,26,"HIGH SCORE");
	mvwprintw(scorebox,1,42,"SCORE");
	mvwprintw(scorebox,1,53,"TIME");
	wattroff(scorebox,A_BOLD);
	wrefresh(scorebox);
	wrefresh(gamebox);

	current_board = MAP_WIDTH/2-4;	//set board at centre
	current_ballX = BOARD_HEIGHT-1;	//set ballX above the board
	current_ballY = MAP_WIDTH/2;		//set ballY at centre

	// initialise map using predefined numbers
	for(h=0; h<MAP_HEIGHT; h++){
		for(w=0; w<MAP_WIDTH; w++){
			if( h==0 | w==0 | w==MAP_WIDTH-1 ){
				map[h][w] = WALL;
			}
			else if (h==MAP_HEIGHT-1){
				map[h][w] = WALL_BOTTOM;
			}
			else if(h==BOARD_HEIGHT && (w>=current_board&&w<=current_board+7)){
				map[h][w] = BOARD;
			}
			else
				map[h][w] = EMPTY;
		}
	}
	map[current_ballX][current_ballY] = BALL;
	test1();
	//	makebrick();
	refreshMap();

   //Press Key to Start popup
   popup("Press Any Key to Start",0,A_BOLD|A_BLINK);
   refreshMap();	//first show map
}

void highscore(int code){
	int temp;
	char buffer[10];
	int fd;
	if(code==0){ //Just Read
		if( (fd=open("score.txt",O_RDONLY))==-1){
			test_high=1000;
		}
		else{
			read(fd,buffer,10);
			temp = atoi(buffer);
			test_high=temp;
		}
	}
	else if(code==1){ //Update highscore
		fd=open("score.txt",O_CREAT|O_WRONLY);
		sprintf(buffer,"%d",test_high);
		write(fd,buffer,10);
	}
	close(fd);
}
