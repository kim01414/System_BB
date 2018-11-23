#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "BB.h"

PLATE p;
BALL b = {0,1,29,19};
BRICK field[13][56];

int score=0;
int THkill = 0;

int main()
{
    int ch;
    int thr_id[3];
    pthread_t p_thread[3]; 
    initialize();
    thr_id[0] = pthread_create(&p_thread[0],NULL,canon,NULL);
    //thr_id[1] = pthread_create(&p_thread[1],NULL,status,NULL);
    //thr_id[2] = pthread_create(&p_thread[2],NULL,reset,NULL);
    keypad(stdscr,TRUE);
    keypad(gamebox,TRUE);
    while(THkill!=1)
    {
        ch = wgetch(gamebox);
        if(ch==KEY_LEFT) moves(-1);
        else if(ch==KEY_RIGHT) moves(1);
    }
    echo();
    clear();
    refresh();
    endwin();
    return 0;
}

void brick()
{
    int i,j;
    for(i=0 ; i<13 ; i++)
    {
        for(j=0 ; j<57 ; j++)
        {
            if(CUR.code==1)
            {
              wmove(gamebox,i+1,j+1);  
              waddch(gamebox,ACS_BOARD);
            } 
        }
    }
}

void load(char *level)
{
   char temp;
   int num=1, i=0, j=0;
   FILE *map;
   map = fopen(level,"r");
   while(!feof(map))
   {
       fscanf(map,"%c",&temp);

       if(temp=='\n') continue;
       CUR.left =NULL;
       CUR.right=NULL;

       if(temp=='0') CUR.code=0; 
       else if(temp=='1')
       {
           CUR.code=1;
           switch(num)
           {
               case 2:  CUR.left = &LEFT;
               case 1:
               {
                  CUR.right = &RIGHT;
                  num++;
                  break;
               }
               case 3:
               {
                  CUR.left = &LEFT;
                  num=1;
                  break;
               }
           }
       }
       j++;
       if(j==57) //Next Line
       {
           i++;
           j==0;
       }
   }
   fclose(map);
}

void *reset()
{
    int i;
    while(1)
    {
    usleep(1500003);
    if(THkill==1) break;
    wclear(ballbox);
    wclear(gamebox);
    box(gamebox,ACS_VLINE,ACS_HLINE);
    box(scorebox,ACS_VLINE,ACS_HLINE);
    //brick();
    refresh();
    mvwprintw(gamebox,p.y,p.x-5,"=====");
    wrefresh(gamebox);
    }
    clear();
}

void* canon()
{
    while(1)
    {
        if(THkill==1) break;

        if(b.dir_y==UP && b.y==1) 
        {
            b.dir_y=-1;
            //b.dir_x *= -1;
        }
        if(b.y+1==23)
        {
            THkill=1;
            popup("GAME OVER",7,A_BOLD);
        }

        if( (b.dir_y==DOWN) && (b.y==p.y-1) && ( (p.parts[0]==b.x) || (p.parts[1]==b.x) || (p.parts[2]==b.x) || (p.parts[3]==b.x) || (p.parts[4]==b.x) ) )
        {
            b.dir_y=UP;
            if(b.x==p.parts[0] || b.x==p.parts[1])  b.dir_x = -1;
            else if(b.x==p.parts[3] || b.x==p.parts[4]) b.dir_x = 1;
        }  

        if(b.x==1) b.dir_x=1;
        else if(b.x==57) b.dir_x=-1;

        mvwaddstr(gamebox, b.y, b.x, " ");
        
        if(b.dir_y==UP) b.y -=1;
        else if(b.dir_y==DOWN) b.y+=1;
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(b.dir_x==-1) b.x -=1;
        else if(b.dir_x==1) b.x+=1;

        mvwaddstr(gamebox,b.y, b.x, "O");
        usleep(80001);
        wrefresh(gamebox);
    }
}

void* status()
{
    mvwprintw(scorebox,3,3,"STAGE    ");
    mvwprintw(scorebox,4,3,"LIFE     ");
    mvwprintw(scorebox,5,3,"TIME    ",score++);
    while(1) 
    {
        if(THkill==1) break;
        mvwprintw(scorebox,3,14,"#01");
        mvwprintw(scorebox,4,14,"@@@");
        mvwprintw(scorebox,5,14,"%04d",score++);
        usleep(100002);
        wrefresh(scorebox);
    }
    clear();
}

void moves(int dx)
{
    int i;
    if( (p.x+dx==59) || (p.x+dx==5) ) return;
    mvwaddstr(gamebox,20,p.x-5,"     ");
    mvwaddstr(gamebox,20,p.x+dx-5,"=====");
     getyx(gamebox,p.y,p.x);
    for(i=0 ; i<5 ; i++) p.parts[i] = p.x-5+i;
    wrefresh(gamebox);
}

void initialize()
{
    int i;
    initscr();
    noecho();
    curs_set(0);
    //load("lv1.txt");
    gamebox = newwin(24,59,0,1);  //1~22, 1~57
    scorebox = newwin(9,20, 5,60 );

    box(gamebox,ACS_VLINE,ACS_HLINE);
    box(scorebox,ACS_VLINE,ACS_HLINE);

    wattron(scorebox,A_BOLD);
    wattron(gamebox,A_BOLD);
    wattrset(stdscr,A_BOLD|A_STANDOUT);
    wattron(ballbox,A_BOLD);
    
    mvprintw(2,64,"Brick Breaker");
    wattroff(stdscr,A_BLINK|A_STANDOUT);
    mvprintw(3,67,"Ver 0.1");
    mvwprintw(scorebox,1,7,"Status");
    refresh();
    wrefresh(gamebox);
    wrefresh(scorebox);
    wrefresh(ballbox);
    popup("Press Any Key to Start!",0,A_BOLD|A_BLINK);
    mvwprintw(ballbox,11,17,"                        ");
    mvwprintw(gamebox,20,27,"=====");
    getyx(gamebox,p.y,p.x);
    for(i=0 ; i<5 ; i++) p.parts[i] = p.x-5+i;
    mvwprintw(gamebox,29,19,"O");
    refresh();
    wrefresh(gamebox);
    wrefresh(scorebox);
}