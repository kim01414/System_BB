#include "BB.h"

int map[MAP_HEIGHT][MAP_WIDTH];
int current_board;
int current_ballX, current_ballY;
int dx=-1, dy=-1;		//ball delta
int bricks[5]={0,0,0,0,0};
int brick_left=0;
int test_score=0, test_time=-1, test_high, speed=NORMAL,lock=0;
pthread_mutex_t lock1=PTHREAD_MUTEX_INITIALIZER;
pthread_t ballThread, TimeThread;
int maplevel = 1;
WINDOW *gamebox, *scorebox, *welcome;

FILE* fp;
FILE* mapfp;

int main(){
	int h, w; 		//height and width variables for loop
	int stat=1, c=1;	//don't care variables..? not quite importent things
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

	fp = fopen("log.txt", "w");

	while(maplevel < 4 && maplevel > 0){
		mainmenu();
		/*	Initialize	*/
		highscore(0,maplevel-1);
		if( (stat=initialize() )!=0 ) continue;
		test_time=0;
		while(test_time!=-1){
			fprintf(fp, "ballX: %d, ballY: %d, deltaX: %d deltaY: %d\n", current_ballX, current_ballY, dx, dy);
			c=wgetch(stdscr);	
			if(c=='\n' && lock!=1) hold(); //Game pause
			else{
				setBoard(c);		//handle arrow key
				refreshMap();		//loop continue
			}
		}
		brick_left=0; //if game over
	}
	endwin();	//end curses
	return 0;
}

void refreshMap(){ /////////// █ ░ ▒ ▓
	int h, w;
	mvwprintw(scorebox,2,6,"%3d",maplevel);
	mvwprintw(scorebox,5,3,"%8d",test_high);
	mvwprintw(scorebox,8,3,"%8d",test_score);
	mvwprintw(scorebox,14,3,"%8d",brick_left);
	mvwprintw(scorebox,18,3,"(%2d, %2d)",current_ballY,current_ballX);
	if(test_time!=-1)mvwprintw(scorebox,11,8,"%3d",test_time);
	else mvwprintw(scorebox,11,8,"  0");
	pthread_mutex_lock(&lock1);
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
				waddch(gamebox,'o'|A_BOLD);
			}
			else if(map[h][w]==BRICKU){
				waddch(gamebox,' ');
			}
			else if(map[h][w]==BRICKE){
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(3));
			}
			else if(map[h][w]==BRICK3){
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(6));
			}
			else if(map[h][w]==BRICK2) {
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(5));
			}
			else if(map[h][w]==BRICK1) {
				waddch(gamebox,ACS_CKBOARD|COLOR_PAIR(4));
			}
		}
	}
	wrefresh(gamebox);
	wrefresh(scorebox);
	pthread_mutex_unlock(&lock1);
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
	if(brick_left==0){
		test_time=-1;
		popup("GAME CLEAR!",5,A_BOLD);
		highscore(1,maplevel-1);
		test_time=-1;
		test_score=0;
		wclear(gamebox);
		return;
	}
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
			highscore(1,maplevel-1);
			test_time=-1;
			test_score=0;
			popup("GAME OVER",6,A_BOLD);
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
			}

      else if(temp_y > current_board+2 && temp_y <= current_board+4){
				dx *= -1;

				if(dy == 1){
					map[current_ballX][current_ballY] = EMPTY;
					current_ballY += 1;
				}
				else if(dy == -1){
					map[current_ballX][current_ballY] = EMPTY;
					current_ballY -= 1;
				}
				dy = 0;
			}

			else if(temp_y > current_board+4 && temp_y <= current_board+7) {
				dx *= -1;

				if(dy == 0)
					dy = 1;
			}

		} // if(map[temp_x][temp_y] == BRARD). END

			else if(map[temp_x][temp_y] == WALL || map[temp_x][temp_y] == WALL_BOTTOM) {
				if(temp_y == 0 || temp_y == MAP_WIDTH-1) {	// meet right, left wall
					dy *= -1;
				if(map[current_ballX + dx][current_ballY + dy] == BOARD)
					dx *= -1;

			}

			else if(temp_x == 0 || temp_y == MAP_HEIGHT-1) {	// meet up, down wall
				dx *= -1;
				if(map[current_ballX + dx][current_ballY + dy] == WALL)
					dy *= -1;
			}

		} //else if(map[temp_x][temp_y] == WALL || ...). END

		else {
			if(map[current_ballX+dx][current_ballY+dy] && map[current_ballX-dx][current_ballY+dy]) {

				deleteBrick(what, dx, dy, FALSE);
				dx *= -1;
				dy *= -1;


/*			while(map[current_ballX+dx][current_ballY+dy] && map[current_ballX-dx][current_ballY+dy])
			{
					map[current_ballX][current_ballY] = EMPTY;
					deleteBrick(what, dx, dy, FALSE);
					dx *= -1;

					if(dy == 1)
						current_ballY++;
					if(dy == -1)
						current_ballY--;

					refreshMap();
			} */

			}

			else
			{
				deleteBrick(what, dx, dy, FALSE);
				dx *= -1;
			}
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
	pthread_mutex_trylock(&lock1);
	if(!boomFlag) {
		xpos = current_ballX+x;
		ypos = current_ballY+y;
		temp = ypos;
		fprintf(fp, "    Brick hit!, brick: %d, brickposition: %d, %d\n", what, xpos, ypos);
	}

	if(boomFlag) { // block position.
		xpos = x;
		ypos = y;
		temp = ypos;
		what = map[x][y];
		if(what)
			fprintf(fp, "    Brick explosion!, brick: %d, brickposition: %d, %d\n", what, xpos, ypos);

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

		if(what==BRICK1) brick_left--;
		// bricks counter.
	}

	// 2. explosive bricks control.
	/* left hit, -1 left bricks. right hit, -1 right bricks.
	   top and bottom hit, remove top bottom bricks.
	   using recursive call. and flag.       	       */
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

		if(map[xpos][ypos+2] != EMPTY || map[xpos][ypos+2] != WALL) {
			deleteBrick(map[xpos][ypos+2] ,xpos, ypos+2, TRUE);
		} // right

		//top and bottom is broke always.
		if (map[xpos+3][ypos] != EMPTY || map[xpos+3][ypos] != WALL) {
			deleteBrick(map[xpos+3][ypos], xpos+3, ypos, TRUE);
			deleteBrick(map[xpos-3][ypos], xpos-3, ypos, TRUE);
		} // top and bottom.

		if (map[xpos-3][ypos] != EMPTY || map[xpos-3][ypos] != WALL) {
			deleteBrick(map[xpos+3][ypos], xpos+3, ypos, TRUE);
			deleteBrick(map[xpos-3][ypos], xpos-3, ypos, TRUE);
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
	pthread_mutex_unlock(&lock1);
}

void BOX(WINDOW* win, int X,int Y, int color){
	box(win,ACS_VLINE|color,ACS_HLINE|color);
	mvwaddch(win, 0,  0   , ACS_ULCORNER|color);
	mvwaddch(win, 0,  X-1 , ACS_URCORNER|color);
	mvwaddch(win, Y-1, 0  , ACS_LLCORNER|color);
	mvwaddch(win, Y-1, X-1, ACS_LRCORNER|color);
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
			mvwaddstr(welcome,15,37,"Help");
		if(sel==2) wattron(welcome,A_DIM);

		//if(sel==3) wattroff(welcome,A_DIM);
		//	mvwaddstr(welcome,16,35,"Settings");
		//if(sel==3) wattron(welcome,A_DIM);

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
				help();
				sel=1;
			}
			else if(sel==1) {
				Select();
				if(maplevel!=-1){
					clear();
					refresh();
					delwin(welcome);
					return;
				}
			}
		}
	}

}

int initialize() //80 x 26
{
	int h, w;
	char ch;
	clear();		//initialise screen
	curs_set(0);	//make user can't see the cursor
	noecho();
	keypad(stdscr, TRUE);	//enables the reading of func keys(arrow keys)
	test_score=0;
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	init_pair(4,COLOR_BLUE,COLOR_WHITE);
	init_pair(5,COLOR_GREEN,COLOR_WHITE);
	init_pair(6,COLOR_CYAN,COLOR_BLACK);
	gamebox = newwin(22,62,1,0);
	scorebox = newwin(22,17,1,63);
	wattron(gamebox,COLOR_PAIR(1));
	BOX(gamebox,62,22,COLOR_PAIR(2));
	box(scorebox,ACS_VLINE,ACS_HLINE);
	refresh();
	wattron(scorebox,A_BOLD);
	mvwprintw(scorebox,1,6, " MAP ");
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
	mvwprintw(scorebox,13,3,"BRICK COUNT");

	wrefresh(scorebox);
	wrefresh(gamebox);

	switch(maplevel) {
	case 1: mapfp = fopen("map1.txt", "r"); break;
	case 2: mapfp = fopen("map2.txt", "r"); break;
	case 3:	mapfp = fopen("map3.txt", "r"); break;
	case 4:	mapfp = fopen("map4.txt", "r"); break;
	case 5:	mapfp = fopen("map5.txt", "r"); break;
	}

	if(!mapfp){
		popup("Cannot open MAP file!",0,A_BOLD);
		return 1;
	}

	for(int i = 0; i < MAP_HEIGHT; i++)
		for(int j = 0; j < MAP_WIDTH; j++){
			fscanf(mapfp, "%d ", &map[i][j]);
			switch(map[i][j]){
				case BRICK1: bricks[0]++; break;
				case BRICK2: bricks[1]++; break;
				case BRICK3: bricks[2]++; break;
				case BRICKE: bricks[3]++; break;
				case BRICKU: bricks[4]++; break;
			}
		}

	for(w=0 ; w<5; w++) {
		bricks[w]/=3;
		brick_left+=bricks[w];
		bricks[w]=0;
	}

	current_board = MAP_WIDTH/2-4;	//set board at centre
	current_ballX = BOARD_HEIGHT-1;	//set ballX above the board

	for(int i = 0; i < 8; i++)
		map[BOARD_HEIGHT][current_board+i] = BOARD;


	current_ballY = MAP_WIDTH/2;	//set ballY at centre
	map[current_ballX][current_ballY] = BALL;
	refreshMap();

   //Press Key to Start popup
   popup("Press Any Key to Start", 0, A_BOLD|A_BLINK);
   refreshMap();	//first show map
   return 0;
}

void highscore(int code, int level){
	int temp;
	char* files[4]={"score1.txt","score2.txt","score3.txt","score4.txt"};
	char buffer[10];
	int fd;
	if(code==0){ //Just Read
		if( (fd=open(files[level],O_RDONLY))==-1){
			test_high=1000;
		}
		else{
			read(fd,buffer,10);
			temp = atoi(buffer);
			test_high=temp;
		}
	}
	else if(code==1){ //Update highscore
		fd=open(files[level],O_CREAT|O_WRONLY);
		sprintf(buffer,"%d",test_high);
		write(fd,buffer,10);
	}
	close(fd);
}
