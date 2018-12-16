#include "BB.h"

int map[MAP_HEIGHT][MAP_WIDTH];
int current_board;
int current_ballX, current_ballY;
int dx=-1, dy=-1;		//ball delta
int brick_left=0;
int test_stage=1, test_score=0, test_time=-1, test_high, speed=SLOW;
pthread_t ballThread, TimeThread;

WINDOW *gamebox, *scorebox, *welcome;

int main(){
	int h, w; 		//height and width variables for loop
	int q=1, c=1;	//don't care variables..? not quite importent things
	char ch;
	//to make ball thread
	int thr_id, status;
	initscr();
	start_color();
	init_color(COLOR_MAGENTA,105,105,105);
	init_pair(7,COLOR_MAGENTA,COLOR_BLACK);
	curs_set(0);	//make user can't see the cursor
	noecho();
	refresh();
	pthread_create(&ballThread, NULL, ballThreadFunc, (void*)&c);
	pthread_create(&TimeThread, NULL, stopwatch, NULL);
	while(1){

		mainmenu();
		/*	Initialize	*/
		highscore(0);
		initialize();
		test_time=0;
		while(test_time!=-1){
			c=wgetch(stdscr);	//if user input arrow key
			setBoard(c);		//handle arrow key
			refreshMap();		//loop continue
		}
	}
	endwin();	//end curses
	return 0;
}

void test1(){
	int i, j;

	for(i=3; i<4; i+=2) {
		for(j = 7; j < MAP_WIDTH-7; j++) {
			map[i][j] = BRICK3;
			brick_left += 2;
			if(j %4 == 1) j++;
		}
	}

	/*for(i=5; i<6; i+=2) {
		for(j = 7; j < MAP_WIDTH-7; j++) {
			map[i][j] = BRICK2;
			brick_left += 2;
			if(j %4 == 1) j++;
		}
	}*/


	for(i=9; i<10; i+=2) {
		for(j = 7; j < MAP_WIDTH-7; j++) {
			map[i][j] = BRICKE;
			brick_left += 2;
			if(j %4 == 1) j++;
		}
	}


	for(i=5; i<6; i+=2) {
		for(j = 7; j < MAP_WIDTH-7; j++) {
			map[i][j] = BRICKU;
			brick_left += 2;
			if(j %4 == 1) j++;
		}
	}


	for(i=7; i<8; i+=2) {
		for(j = 7; j < MAP_WIDTH-7; j++) {
			map[i][j] = BRICK1;
			brick_left += 2;
			if(j %4 == 1) j++;
		}
	}


}

void refreshMap(){ /////////// █ ░ ▒ ▓
	int h, w;
	mvwprintw(scorebox,2,6,"%3d",test_stage);
	mvwprintw(scorebox,5,3,"%8d",test_high);
	mvwprintw(scorebox,8,3,"%8d",test_score);
	if(test_time!=-1)mvwprintw(scorebox,11,8,"%3d",test_time);
	else mvwprintw(scorebox,11,8,"  0");

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
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(3));
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
	while(1){
		if(test_time!=-1)setBallPos();
	}
	pthread_exit(NULL);
}

void* stopwatch(){
	while(1){
		if(test_time!=-1){
			test_time++;
			sleep(1);
		}
	}
	pthread_exit(NULL);
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
		case BRICKE:
		case BRICKU:
			setBallDel(temp);
			test_score+=100;
			if(test_score>=test_high) test_high=test_score;
			break;
		case WALL_BOTTOM:	//when next pos is bottom, game end
			highscore(1);
			test_time=-1;
			gameover(test_score,test_high);
			wclear(gamebox);
			return;
	}


	//make prev ball to empty
	map[current_ballX][current_ballY]=EMPTY;
	//set new position
	current_ballX+=dx;
	current_ballY+=dy;
	map[current_ballX][current_ballY]=BALL;

	refreshMap();
	usleep(speed);
}



void setBallDel(int what){
	int temp_x = current_ballX + dx;
	int temp_y = current_ballY + dy;


	if(map[temp_x][temp_y] != EMPTY){
		if(map[temp_x][temp_y] == BOARD){	// meet board
			// change delta despite board's position

			if(temp_y <= current_board+2 ){
				dx *= -1;
				if(dy == 0)
					dy = -1;


			}else if(temp_y > current_board+2 && temp_y <= current_board+4){
				dx *= -1;
				dy = 0;

			}else if(temp_y > current_board+4 && temp_y <= current_board+7){
				dx *= -1;
				if(dy == 0)
					dy = 1;

			}

		} else if(map[temp_x][temp_y] == WALL || map[temp_x][temp_y] == WALL_BOTTOM){
			if(temp_y == 0 || temp_y == MAP_WIDTH-1){	// meet right, left wall
				dy *= -1;
				if(map[current_ballX + dx][current_ballY + dy] == BOARD)
					dx *= -1;

			}else if(temp_x == 0 || temp_y == MAP_HEIGHT-1){// meet up, down wall
				dx *= -1;
				if(map[current_ballX + dx][current_ballY + dy] == WALL)
					dy *= -1;
			}

		}else{									// meet bricks
			deleteBrick(what, dx, dy, FALSE);
			dx *= -1;
		}
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

void deleteBrick(int what, int x, int y, int boomFlag)
{
	int xpos = current_ballX+x, ypos = current_ballY+y;
	int temp = ypos;

	if(!boomFlag) {
		xpos = current_ballX+x;
		ypos = current_ballY+y;
		temp = ypos;
	}

	if(boomFlag) {
		xpos = x;
		ypos = y;
		temp = ypos;
//		what = map[x][y];
	}

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
		}

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp] = 0;
		}
		brick_left--; // bricks counter.

		//explosive function.
		if(map[xpos][ypos-2] != EMPTY || map[xpos][ypos-2] != WALL) {
			deleteBrick(map[xpos][ypos-2] ,xpos, ypos-2, TRUE);
		} // left

		else if(map[xpos][ypos+2] != EMPTY || map[xpos][ypos+2] != WALL) {
			deleteBrick(map[xpos][ypos+2] ,xpos, ypos+2, TRUE);
		} // right

		else if (map[xpos+1][ypos] != EMPTY || map[xpos+1][ypos] != WALL) {
			deleteBrick(map[xpos+2][ypos], xpos+2, ypos, TRUE);
			deleteBrick(map[xpos-2][ypos], xpos-2, ypos, TRUE);
		} // top and bottom.

		else if (map[xpos-1][ypos] != EMPTY || map[xpos-1][ypos] != WALL) {
			deleteBrick(map[xpos+2][ypos], xpos+2, ypos, TRUE);
			deleteBrick(map[xpos-2][ypos], xpos-2, ypos, TRUE);
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


void mainmenu()
{
	int sel=1,c;
	welcome = newwin(22,80,1,0);

	keypad(welcome,TRUE);
	wattron(welcome,A_BOLD);
	wclear(welcome);
	while(1)
	{
		wattroff(welcome,A_DIM);
		title();
		box(welcome,ACS_VLINE,ACS_HLINE);
		wattron(welcome,A_DIM);
		if(sel==1) wattroff(welcome,A_DIM);
			mvwaddstr(welcome,14,34,"Start Game");
		if(sel==1) wattron(welcome,A_DIM);

		if(sel==2) wattroff(welcome,A_DIM);
			mvwaddstr(welcome,15,35,"Settings");
		if(sel==2) wattron(welcome,A_DIM);

		if(sel==3) wattroff(welcome,A_DIM);
			mvwaddstr(welcome,16,35,"About us");
		if(sel==3) wattron(welcome,A_DIM);

		if(sel==4) wattroff(welcome,A_DIM);
			mvwaddstr(welcome,17,37,"Exit");
		if(sel==4) wattron(welcome,A_DIM);

		wrefresh(welcome);
		c=wgetch(welcome);
		if(c==KEY_UP){
			sel--;
			if(sel<1) sel=4;
		}
		else if(c==KEY_DOWN){
			sel++;
			if(sel>4) sel=1;
		}
		else if(c=='\n'){
			if(sel==4){
				clear();
				endwin();
				exit(0);
			}
			else if(sel==3) {
				about();
				sel=1;
			}
			else if(sel==2){
				settings(NULL);
				sel=1;
			}
			else if(sel==1) {
				clear();
				refresh();
				delwin(welcome);
				return;
			}
		}
	}

}

void initialize() //80 x 26
{
	int h, w;
	char ch;
	clear();		//initialise screen
	curs_set(0);	//make user can't see the cursor
	noecho();
	keypad(stdscr, TRUE);	//enables the reading of func keys(arrow keys)
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	init_pair(4,COLOR_BLUE,COLOR_WHITE);
	init_pair(5,COLOR_GREEN,COLOR_WHITE);
	init_pair(6,COLOR_GREEN,COLOR_BLACK);
	attron(A_BOLD|COLOR_PAIR(6));
	gamebox = newwin(22,62,1,0);
	scorebox = newwin(22,17,1,63);
	wattron(gamebox,COLOR_PAIR(1));
	BOX(gamebox,62,22,COLOR_PAIR(2));
	box(scorebox,ACS_VLINE,ACS_HLINE);
	refresh();
	wattron(scorebox,A_BOLD);
	mvwprintw(scorebox,1,6, "STAGE");
	for(h=0 ; h<17 ; h++){
		if(h==0){
			mvwaddch(scorebox,3,0,ACS_LTEE);
			mvwaddch(scorebox,6,0,ACS_LTEE);
			mvwaddch(scorebox,9,0,ACS_LTEE);
			mvwaddch(scorebox,12,0,ACS_LTEE);
		}
		else if(h==16){
			mvwaddch(scorebox,3,16,ACS_RTEE);
			mvwaddch(scorebox,6,16,ACS_RTEE);
			mvwaddch(scorebox,9,16,ACS_RTEE);
			mvwaddch(scorebox,12,16,ACS_RTEE);
		}
		else{
			mvwaddch(scorebox,3,h,ACS_HLINE);
			mvwaddch(scorebox,6,h,ACS_HLINE);
			mvwaddch(scorebox,9,h,ACS_HLINE);
			mvwaddch(scorebox,12,h,ACS_HLINE);
		}
	}
	mvwprintw(scorebox,4,4,"HIGH SCORE");
	mvwprintw(scorebox,7,6,"SCORE");
	mvwprintw(scorebox,10,7,"TIME");

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
