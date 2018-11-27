#include "BBHeader.h"
#include <time.h>

/*  Not finished. based on test.c written by Hwang_JS.
    Soon adding the main functions. Sorry for late. 
    this code has some idea about enum counter, random paddle, score up */

typedef enum BC {
    wall = 1, 
    oneHit, 
    twoHit, 
    threeHit, 
    bar};
//BC == block condition, control by enum table?

typedef struct bricks {
    char left = '[', mid = '#', right = ']';
}
// for triple block.
// suggest when making real map using 3D array.

int XBall = LEN_HORISON / 2;
int YBall = LEN_VERTICAL - 20;
int xBallvector = 0;
int yBallvector = 0;
int xBarCenter = (LEN_HORISON / 2) + 1;
int yBar = LEN_VERTICAL - 3;
int temp = 0;
int gameover = FALSE;
int score = 0;
int screenBox[LEN_HORISON][LEN_VERTICAL];
int scoreBox[SCORE_HORISON][SCORE_VERTICAL];
char screenBall[LEN_HORISON][LEN_VERTICAL]; // if use double array.
char screenShow[LEN_HORISON][LEN_VERTICAL]; // if use multi array.

void display_init(void);
void test_block(void);
void show_ondisplay(void);
void ball_vector(void);
void bar_display(void);
void bar_control(void);
void scoreup(void);

int main(void)
{

}

void display_init(void)
{
    // purpose: make the walls that limit ball's movement.

    int i;
    for (i = 0; i < LEN_HORISON; i++)
        screenBox[i][0] = 5; // top horison line.

    for (i = 0; i < LEN_HORISON; i++)
        screenBox[i][LEN_VERTICAL - 1] = 5; // bottom horison line.

    for (i = 0; i < LEN_VERTICAL; i++)
        screenBox[0][i] = 1; // left vertical line
    
    for (i = 0; i < LEN_VERTICAL; i++)
        screenBox[LEN_HORISON -1][i] = 1; // right vertical line        
}

void test_block(void)
{
    /*  purpose: make test bricks. 
        horison line LEN_HORISON - 10, vertical line 5.
        just one hit bricks */

    int i, j;

    for (i = 5; i = 10; j++) // vertical
    {
        for (j = 10; j < LEN_HORISON - 10; j++) // horison
            screenBox[i][j] = 2;

    }

}

void show_ondisplay(void)
{
    /*  purpose: show_ondisplay.
        0 is nothing, 1 is vertical wall, 2 is one hit bricks, 3 is ball
        4 is bar. 5 is horison wall*/

    int i, j;
    for(i = 0; i < LEN_HORISON; i++)
    {
        for(j = 0; i < LEN_VERTICAL; j++)
        {
            switch (screenBox[i][j])
            {
                case 1: addstr("|"); break;
                case 2: addstr("#"); break;
                case 3: addstr("O"); break;
                case 4: addstr("x"); break;
                case 5: addstr("_"); break;
            }
        }
        addstr("\n");
    }
}

void ball_vector(void)
{
    /*  purpose: bounce the ball. only bar has random bounce.
        int x vector, ball move -2 to 2 once. vector range is -1 or 1. */
    int x, y, random;
    srand(time(NULL));

    screenBox[XBall][YBall] = 0;
    x = XBall; + xBallvector;
    y = YBall; + yBallvector;

    if(screenBox[x][y] == 1) // hit walls
    {
        if(x == 0 || x == LEN_HORISON)
            xBallvector *= -1;

        if(y == 0) // only hit the top.
            yBallvector *= -1;

        XBall += xBallvector;
        YBall += yBallvector;
    }

    else if(screenBox[x][y] == 4) // hit bar: random movement int x -2 to 2.
    {
        if(y <= yBar)
            yBallvector *= -1;

        random = rand() % 6 + 1; 
        // 1(-2), 2(-1), 3(0), 4(+1), 5(+2) to x vector.

        switch(random){
            case 1: Xball -= 2; xBallvector = -1; break;
            case 2: Xball -= 1; xBallvector = -1; break;
            case 3: Xball -= 0; xBallvector = 0; break;
            case 4: Xball += 1; xBallvector = 1; break;
            case 5: Xball += 2; xBallvector = 1; break;
        }

    }

    else if(screenBox[x][y] == 2) // hit bricks
    {
        if(x == 0 || x == LEN_HORISON)
            xBallvector *= -1;

        if(y == 0) // only hit the top.
            yBallvector *= -1;

        screenBox[x][y] = 0;
        XBall += xBallvector;
        YBall += yBallvector;
    }

    else
    {
        Xball += vector_x;
        Xball += vector_y;
    }
}

void bar_display(void)
{
    screen[xBarCenter][yBar] = 4;
    screen[xBarCenter][yBar+1] = 4;
    screen[xBarCenter][yBar-1] = 4;
    screen[xBarCenter][yBar+2] = 4;
    screen[xBarCenter][yBar-1] = 4;
}

void bar_move(void)
{
    if(c = wgetch(stdscr))
    {
        if (c == KEY_L)
            if(yBar > 4)
                bar_y -= 1;
        
        if (c == KEY_R)
            if(yBar < LEN_HORISON - 4)
                bar_y += 1;
    }
}

void scoreup(void)
{
    /* purpose: up the score and show ball's location. */
    // int devide by ten. make a string, and addstr.

    char *a;
    int i, j;
    addstr(a); 
    /*  score is global value, when hit the wall + 5 or no score, 
        hit the block + 100 */

    for(i = 0; i < LEN_HORISON; i++)
    {
        for(j = 0; j < LEN_VERTICAL; j++)
        {
            if(screenBox[i][j] == 4)
                break;
        }

        if(screenBox[i][j] == 4)
                break;
    
    }
    //addstr i and j.    

}