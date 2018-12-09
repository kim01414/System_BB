#include "Bricks.h"

void deleteBrick(int what, int x, int y)
{
	int xpos = current_ballX+x, ypos = current_ballY+y;
	int temp = ypos;

	// 1. normal bricks control.
	if(what == BRICK3 || what == BRICK2 || what == BRICK1) {
		map[xpos][ypos]--;
		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp]--;
		} // for left bricks

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp]--;
		} // for right bricks

		brick_left--;
		// bricks counter.
	}

	// 2. explosive bricks control.
	/* left hit, -1 left bricks. right hit, -1 right bricks.
	   top and bottom hit, remove top bottom bricks.
	   using recursive call.	             	       */
	else if(what == BRICKE) {
		map[xpos][ypos] = 0;

		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp] = 0;
		{

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp] = 0;
		}
		brick_left--; // bricks counter.

		//explosive function.
		if(map[xpos][ypos-2] != EMPTY || map[xpos][ypos-2] != WALL) {
			deletebrick(map[xpos][ypos-2] ,xpos, ypos-2);
		} // left

		else if(map[xpos][ypos+2] != EMPTY || map[xpos][ypos+2] != WALL) {
			deletebrick(map[xpos][ypos+2] ,xpos, ypos+2);
		} // right

		else if (map[xpos+1][ypos] != EMPTY || map[xpos+1][ypos] != WALL) {
			deletebrick(map[xpos+1][ypos], xpos+1, ypos);
			deletebrick(map[xpos-1][ypos], xpos-1, ypos);
		} // top and bottom.

		else if (map[xpos-1][ypos] != EMPTY || map[xpos-1][ypos] != WALL) {
			deletebrick(map[xpos+1][ypos], xpos+1, ypos);
			deletebrick(map[xpos-1][ypos], xpos-1, ypos);
		} // top and bottom.

	} // left brick remove.


	// 3. invisible bricks control.
	else if(what == BRICKU) {
		map[xpos][ypos] = 1;
		while(map[xpos][--temp]!=EMPTY) {
			map[xpos][temp] = 1;
		} // make it level one block. left

		temp = ypos;
		while(map[xpos][++temp]!=EMPTY) {
			map[xpos][temp] = 1;
		} // right

		brick_left--;
                // bricks counter.
	}

}
