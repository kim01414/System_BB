#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>

#define MAP_WIDTH 62	//except 2 wall lines,  make centre map to  60*20
#define MAP_HEIGHT 22
#define BOARD_HEIGHT MAP_HEIGHT-3	//board moves at map[19][x]
#define BRICK_HEIGHT 10		//brick generated at x : 4~9, y : 7~55

#define WALL 10
#define WALL_BOTTOM 11
#define BRICK1 1
#define BRICK2 2
#define BRICK3 3
#define BRICKE 7 // explosion
#define BRICKU 8 // invisiable
#define BOARD 4
#define BALL 5
#define EMPTY 0

///////////SPEED/////////////
#define SLOW 200000
#define NORMAL 100000
#define FAST 50000
// global values
/*int map[MAP_HEIGHT][MAP_WIDTH];
int current_board;
int current_ballX, current_ballY;
int dx=-1, dy=-1;		//ball delta
int brick_left=0;
int test_stage=1, test_score=0, test_time=0, test_high;
*/
// board functions
void setBoard(int c);
void moveBoard(int d);


// ball functions
void setBallPos();
void setBallDel(int what);
void *ballThreadFunc(void*);


//brick functions
void makebrick();
void deleteBrick(int what, int x, int y);


// map functions
void refreshMap();
void initialize();
void popup(char*,int,int);

//UI
void title();
void *stopwatch();
void gameover(int,int);
void highscore(int);
void BOX(WINDOW*, int, int,int);
void mainmenu();
void about();
void settings(int*);

//MAP design
void test1();
