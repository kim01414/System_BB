#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <time.h>
#include <stdlib.h>

#define LENGTH 40
#define LENGTH2 80
#define TRUE 1
#define FALSE 0
#define KEY_LEFT 0404
#define KEY_RIGHT 0405


int ball_x = 0;
int ball_y = 0;

int vector_x = 1;
int vector_y = -1;

int bar_x = LENGTH-3;
int bar_y = LENGTH;

int c = 0;

int game_over = FALSE;


int screen[LENGTH][LENGTH2] = { 0, };
char screen1[LENGTH][LENGTH2] = {' '};
// WINDOW* progress





void make_Display(){

		for (int i = 0; i < LENGTH; i++) {	//화면 초기화
			for (int j = 0; j < LENGTH2; j++) {
				if (i == 0 || i == LENGTH - 1)
				screen[i][j] = 1;	// 틀 만들기
				
				if (j == 0 || j == LENGTH2-1)
				screen[i][j] = 1;
			}
		
	
		}
}


void make_block(int x, int y){

	for(int i = 2; i < 2+x; i++){
		for(int j = y; j < LENGTH2-y; j++){
				screen[i][j] = 2;
		}
	}
}


void print_Display(){
	for (int i = 0; i < LENGTH; i++) {	//화면 초기화
			for (int j = 0; j < LENGTH2; j++) {
				if(screen[i][j] == 1)
				addstr("@");	//make_wall
				else if(screen[i][j] == 0)
				addstr(" ");	//nothing
				else if(screen[i][j] == 2)
				addstr("#");	//make_block
				else if(screen[i][j] == 3)
				addstr("o");	//make_ball
				else if(screen[i][j] == 4)
				addstr("m");

			}
			addstr("\n");
		}
}


void ball_vector(){

	screen[ball_x][ball_y] = 0;

	int x = ball_x + vector_x;
	int y = ball_y + vector_y;	

	if(screen[x][y] == 1){	//meet wall
		if(x == 0 || x == LENGTH-1){	//meet right, left wall
			vector_x *= -1;

		}
		if(y == 0 || y == LENGTH2-1)
			vector_y *= -1;
	
		ball_x += vector_x;
		ball_y += vector_y;
	}
	else if(screen[x][y] == 4){	//meet bar
		vector_x *= -1;
		ball_x += vector_x;
		ball_y += vector_y;
	}
	else if(screen[x][y] == 2){	//meet block

		srand(time(NULL));
		int random = rand();
		random = random%2;

		screen[x][y] = 0;

		if(random == 0){
			vector_x *= -1;
			vector_y *= 1;
		}else if(random == 1){
			vector_x *= 1;
			vector_y *= -1;

		}
		
		ball_x = x;
		ball_y = y;

	}else{
		ball_x += vector_x;
		ball_y += vector_y;
	}

}


void bar_display(){
	screen[bar_x][bar_y] = 4;
	screen[bar_x][bar_y+1] = 4;
	screen[bar_x][bar_y-1] = 4;
	screen[bar_x][bar_y+2] = 4;
	screen[bar_x][bar_y-2] = 4;
}

void bar_move(){

	if(c = wgetch(stdscr)){
		if(c == KEY_LEFT){
			if(bar_y > 4)
				bar_y -= 1;
		}
		
		else if(c == KEY_RIGHT){
			if(bar_y < LENGTH2-4)
				bar_y += 1;
		}
	}
	
}


/////////////////////////////////////////////////////////////////////////////
int main() {
	
	int number = 5;

	ball_y = LENGTH;
	ball_x = LENGTH-5;

	initscr();

	


	make_Display();

	
	make_block(5, number);

	
	while(game_over == FALSE){
		clear();
	
		//bar_move();
		bar_display();
		ball_vector();

		screen[ball_x][ball_y] = 3;
		print_Display();

		refresh();
		usleep(10000);
		//usleep(1000000) == 1 second

		//game_over == TRUE;
		if(game_over == TRUE)
			break;

	}



		refresh();
		addstr("Game Over");
		getch();
	endwin();
}
///////////////////////////////////////////////////////////////////////////
