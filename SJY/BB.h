#define MAP_WIDTH 62	//except 2 wall lines,  make centre map to  60*20
#define MAP_HEIGHT 22
#define BOARD_HEIGHT MAP_HEIGHT-3	//board moves at map[19][x]
#define BRICK_HEIGHT 10		//brick generated at x : 4~9, y : 7~55


#define WALL 10
#define WALL_BOTTOM 11
#define BRICK1 1
#define BRICK2 2
#define BRICK3 3
#define BOARD 4
#define BALL 5
#define EMPTY 0

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
