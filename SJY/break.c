#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>


#define MAP_WIDTH 62	//except 2 wall lines,  make centre map to  60*20
#define MAP_HEIGHT 22
#define BOARDHEIGHT MAP_HEIGHT-3
#define WALL 1
#define WALLBOTTOM 2
#define BOARD 3
#define BRICK 4
#define BALL 5
#define EMPTY 0




int map[MAP_HEIGHT][MAP_WIDTH];
int currentboard;
int currentballX, currentballY;	
int dx=-1, dy=-1;		//ball delta




void setBoard(int c);
void moveBoard(int d);

void setBallPos();
void setBallDel();
void *ballThreadFunc(void*);

void refreshMap();




int main(){
	int h, w, q=1, c=1;
	char ch;

	//to make ball thread
	pthread_t ballThread;
	int thr_id;
	int status;


	/*	Initialise	*/
	initscr();
	clear();		//initialise screen
	curs_set(0);	//make user can't see the cursor
	noecho();
	keypad(stdscr, TRUE);	//enables the reading of func keys(arrow keys)
	

	currentboard = MAP_WIDTH/2-4;	//set board at centre
	currentballX = BOARDHEIGHT-1;	//set ballX above the board
	currentballY = MAP_WIDTH/2;		//set ballY at centre


	for(h=0; h<MAP_HEIGHT; h++){
		for(w=0; w<MAP_WIDTH; w++){
			if( h==0 | w==0 | w==MAP_WIDTH-1 ){
				map[h][w] = WALL;
			}
			else if (h==MAP_HEIGHT-1){
				map[h][w] = WALLBOTTOM;
			}
			else if(h==BOARDHEIGHT && (w>=currentboard&&w<=currentboard+7)){
				map[h][w] = BOARD;
			}
			else
				map[h][w] = EMPTY;
		}
	}
	map[currentballX][currentballY] = BALL;


	refreshMap();	//first show map


	move(MAP_HEIGHT/2,MAP_WIDTH/2-12);
	addstr("Press any key to start");
	ch=getch();

	thr_id = pthread_create(&ballThread, NULL, ballThreadFunc, (void*)&c);

	while(c){
		c=wgetch(stdscr);	//if user input arrow key
		setBoard(c);		//handle arrow key
		refreshMap();		//loop continue
	}
	
	pthread_join(ballThread, (void**)&status);

	echo();
	getch();
	endwin();	//커서 종료
	return 0;
}




void refreshMap(){
	int h, w;


	for(h=0; h<MAP_HEIGHT; h++){
		for(w=0; w<MAP_WIDTH; w++){
			move(h,w);
			if(map[h][w]==EMPTY){
				addch(' ');
			}
			else if(map[h][w]==WALL | map[h][w]==WALLBOTTOM){
				addch('#');
			}
			else if(map[h][w]==BOARD){
				addch('W');
			}
			else if(map[h][w]==BALL){
				addch('O');
			}
		}
	}
	refresh();
}




void setBoard(int c){
	int i, sth;


	switch(c){
		case KEY_LEFT:
			sth = map[BOARDHEIGHT][currentboard-1];	//check left
			if(sth==0){		//empty left
				moveBoard(-1);
			}else if(sth==1){;}// there is wall, don't move
			break;
		case KEY_RIGHT:
			sth = map[BOARDHEIGHT][currentboard+8];	//check right
			if(sth==0){
				moveBoard(1);
			}else if(sth==1){;}
			break;
	}
}


void moveBoard(int d){
	int i;

	if(d==-1){
		map[BOARDHEIGHT][currentboard+7]=0;	//set rightend to empty
		map[BOARDHEIGHT][--currentboard]=3;	//set leftend to board
	}else if(d==1){
		map[BOARDHEIGHT][currentboard]=0;
		map[BOARDHEIGHT][++currentboard+7]=3;
	}
}



void *ballThreadFunc(void* data){
	while(1){
		setBallPos();
	}
}


void setBallPos(){
	int temp;

	temp = map[currentballX+dx][currentballY+dy];
	switch(temp){
		case WALL:	//when next pos is wall, bounce
			setBallDel();
			break;
		case WALLBOTTOM:	//when next pos is bottom, game end
			echo();
			endwin();
			exit(1);
			break;
		case BOARD:		//when next pos is board, bounce
			setBallDel();
			break;
		case BRICK:		//when next pos is brick, break the brick and bounce
			setBallDel();
			break;
	}


	//make prev ball to empty
	map[currentballX][currentballY]=EMPTY;
	//set new position
	currentballX+=dx;
	currentballY+=dy;
	map[currentballX][currentballY]=BALL;

	refreshMap();
	usleep(250000);	
}


void setBallDel(){
	if(map[currentballX][currentballY-1]!=EMPTY){
		//if left is not empty
		dy=1;
	}else if(map[currentballX][currentballY+1]!=EMPTY){
		//if right is not empty
		dy=-1;
	}else if(map[currentballX-1][currentballY]!=EMPTY){
		//if up is not empty
		dx=1;
	}else if(map[currentballX+1][currentballY]!=EMPTY){
		//if down is not empty
		dx=-1;
	}
}
