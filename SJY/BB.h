#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
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
#define SLOW 240000
#define NORMAL 170000
#define FAST 120000
// board functions
void setBoard(int c);
void moveBoard(int d);


// ball functions
void setBallPos();
void setBallDel(int what);
void *ballThreadFunc(void*);


//brick functions
void makebrick();
void deleteBrick(int what, int x, int y, int boomFlag);


// map functions
void refreshMap();
int initialize();
void popup(char*,int,int);

//UI
int hold();
void title();
void *stopwatch();
void highscore(int,int);
void BOX(WINDOW*, int, int,int);
void mainmenu();
void about();

void Select();
void help();


//MAP design
void test1();
