#define UP 1
#define DOWN -1
#define CUR field[i][j] //1~13 1~57
#define LEFT field[i][j-1]
#define RIGHT field[i][j+1]

typedef struct ball
{
    int dir_x;
    int dir_y;
    int x;
    int y;
}BALL;

typedef struct plate
{
    int x;
    int y;
    int parts[5];
}PLATE;

typedef struct bricks
{
    int code;
    struct bricks* left;
    struct bricks* right;
}BRICK;

WINDOW *gamebox, *scorebox,*ballbox;

void initialize();
void moves(int);
void* canon();
void* status();
void* reset();
void load(char*);
void brick();
void popup(char*,int,int);
void Error(char*);