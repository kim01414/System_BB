#include "BBheader.h"
#include <time.h>

/*  Based on test.c written by Hwang_JS.
    Soon adding the main functions. Sorry for late. 
    this code has some idea about enum counter, random paddle, score up */

// main function
int main(void)
{
    int speed = 50000;
    initscr();
    wallset();
    map_level0();
    bar_display();

 /*   for(int i= 0;i < LEN_HORISON; i++)
    {
        for(int j =0; j<LEN_VERTICAL; j++)
        {
            if(screenBox[i][j])
                printf("%d", screenBox[i][j]);
            else    
                printf(" ");
        }
        printf("\n");

    } */


    while(gameover == FALSE)
    {
        clear();

        //bar_display();
        //ball_vector();

        ball_vector();
        show_ondisplay();
        refresh();
        game_over();
        usleep(speed); // 0.5 seconds.
        if(speed >= 21000)
            speed -= 10;
        
    }

    refresh();
    addstr("GameOver");

    getchar();
}

// 1. initialization
void wallset(void)
{
    /*  purpose: make the walls that limit ball's movement.
        set box one main and box two score(didn't made).
    */
   
    int i;

    for (i = 0; i < LEN_HORISON; i++)
        screenBox[i][0] = 2; // left vertical line.

    for (i = 0; i < LEN_HORISON; i++)
        screenBox[i][LEN_VERTICAL - 5] = 2; // right vertical line.

    for (i = 0; i < LEN_VERTICAL -5; i++)
        screenBox[0][i] = 1; // top horison line.
    
    for (i = 0; i < LEN_VERTICAL -5; i++)
        screenBox[LEN_HORISON -1][i] = 1; // bottom horison line.
}

void game_over(void)
{
    int i, j;

    for(i = 0; i < LEN_HORISON; i++)
        for(j= deadline; j < LEN_VERTICAL; j++)        
        {
            if(screenBox[i][j] == 8)
            {
                gameover = 1;
                break;
            }
        }
}

// 2. map lists
void map_level0(void)
{
    for(int i = 10; i < LEN_HORISON; i++)
        screenBox[5][i] = 5;

    for(int i = 10; i < LEN_HORISON; i++)
        screenBox[6][i] = 6;

for(int i = 10; i < LEN_HORISON; i++)
        for(int j = 7; j < 10; j++)
            screenBox[j][i] = 3;

}

// 3. bar movement
void bar_display(void)
{
    screenBox[barxp][baryp] = 7;
    for(int i = 0; i < 8; i++)
    {
        screenBox[barxp][baryp-i] = 7;
        screenBox[barxp][baryp+i] = 7;
    }
}

void bar_control(void)
{
    int KEY_R = 405;
    if(temp = wgetch(stdscr))
    {
        if (temp == KEY_L)
            if(barxp > 2)
                barxp -= 1;
        
        if (temp == KEY_R)
            if(barxp < LEN_HORISON - 2)
                barxp += 1;
    }
}

// 4. ball movement
void ball_vector(void)
{
        /*  purpose: bounce the ball. only bar has random bounce.
        int x vector, ball move -2 to 2 once. vector range is -1 or 1. */
    int x, y, random, p, save = 0;
    srand(time(NULL));

    screenBox[ballY][ballX] = 0;
    y = ballX + ballDx;
    x = ballY + ballDy;
    p = screenBox[x][y];
    
    
    if(screenBox[x][y] == 1 || screenBox[x][y] == 2) // hit walls
    {
        if(p == 1) // vertical wall
        {
            ballDx *= -1;
            ballX += ballDx;
        }
        if(p == 2) // horison wall
        {
            ballDy *= -1;
            ballY += ballDy;
        }

        save = 1;
    }

    else if(screenBox[x][y] == 7) // hit bar: random movement int x -2 to 2.
    {
        if(y <= baryp)
            ballDy *= -1;

        random = rand() % 6 + 1; 
        // 1(-2), 2(-1), 3(0), 4(+1), 5(+2) to x vector.

        switch(random){
            case 1: ballX -= 2; ballDx = -1; break;
            case 2: ballX -= 1; ballDx = -1; break;
            case 3: ballX -= 0; ballDx = 0; break;
            case 4: ballX += 1; ballDx = 1; break;
            case 5: ballX += 2; ballDx = 1; break;
        }

        save = 7;

    }

    else if(p == 3 || p == 4 || p == 6) // hit bricks
    {
        //if(x == 0 || x == LEN_HORISON)
            ballDx *= -1;

        //if(y == 0) // only hit the top.
            ballDy *= -1;

        if(p == 3)
        {
            save = -1;
            screenBox[x][y] = 0;
        }
        else
        {
            save = --p;
            screenBox[x][y] = p;
        }
    }
    
    else if(p == 6)
    {
        //if(x == 0 || x == LEN_HORISON)
        ballDx *= -1;

        //if(y == 0) // only hit the top.
        ballDy *= -1;

        screenBox[x][y] = 0;
        if(--screenBox[x-1][y] == 3)
            screenBox[x-1][y] = 0;
        if(--screenBox[x+1][y] == 3)
            screenBox[x][y-1] = 0;
        if(--screenBox[x][y+1] == 3)
            screenBox[x-1][y] = 0;
        if(--screenBox[x-1][y] == 3)
            screenBox[x-1][y] = 0;

        if(--screenBox[x-1][y-1] == 3)
            screenBox[x-1][y-1] = 0;
        if(--screenBox[x-1][y+1] == 3)
            screenBox[x-1][y+1] = 0;
        if(--screenBox[x+1][y-1] == 3)
            screenBox[x+1][y-1] = 0;
        if(--screenBox[x+1][y+1] == 3)
            screenBox[x+1][y+1] = 0;
 
            save = -1;
    }

    else
    {
        ballX += ballDx;
        ballY += ballDy;
    }

    screenBox[x][y] = 8;
    
    if(save)
        screenBox[x][y] = save;

    if(save == -1)
        screenBox[x][y] = 0;
}

// 5. show on display
void show_ondisplay(void)
{
    /*  purpose: show on display. fallow the enum. */

    int i, j;

    for(i = 0; i < LEN_HORISON; i++)
    {
            for(j = 0; j < LEN_VERTICAL; j++)
        {
            switch (screenBox[i][j])
            {
                case 0: addstr(" "); break;
                case 1: addstr("2"); break;
                case 2: addstr("2"); break;
                case 3: addstr("Q"); break;
                case 4: addstr("W"); break;
                case 5: addstr("R"); break;
                case 6: addstr("E"); break;
                case 7: addstr("M"); break;
                case 8: addstr("*"); break;
            }
        }
        addstr("\n");
    }
}