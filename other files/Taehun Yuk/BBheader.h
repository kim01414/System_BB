#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define KEY_L 0404
#define KEE_R 0405

#define TRUE 1
#define FALSE 0

//need to adjustment
#define LEN_HORISON 41 // using x scale.
#define LEN_VERTICAL 50 // using y scale.

#define SCORE_VERTICAL 30
#define SCORE_HORISON 30

enum BlockCondi {
    HW = 1, VW, ONEHIT, TWOHIT, THREEHIT, EXPLO, BAR, BALL
} BlockCondi; // control maps using enum. BC means block condition.

typedef struct bricks {
    char left, mid, right;
} bricks; // for triple block.

// 1. initialization
void wallset(void);
void scoreup(void);
void game_over(void);
 // variables
int screenBox[LEN_HORISON][LEN_VERTICAL];
int screenBall[LEN_HORISON][LEN_VERTICAL]; // ball, walls
int screenBrick[LEN_HORISON][LEN_VERTICAL]; // ball, walls, bricks
int gameover = FALSE;
int score = 0;
int temp = 0;

// 2. map lists
void map_level0(void);
 // variables

// 3. bar movement
void bar_display(void);
void bar_control(void);
 // variables
int barxp = LEN_HORISON - 5;
int baryp = LEN_VERTICAL / 2;

// 4. ball movement
void ball_vector(void);
 // variables
int ballX = LEN_HORISON / 2;
int ballY = LEN_VERTICAL - 20;
int ballDx = 0;
int ballDy = 1; // drop the ball.
int deadline = LEN_VERTICAL - 5; // When ball over here, gameover.

// 5. show on display
void show_ondisplay(void);
 // variables

