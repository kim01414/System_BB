
void setBallDel(int what){
	int temp_x = current_ballX + dx;
	int temp_y = current_ballY + dy;

	
	if(map[temp_x][temp_y] != EMPTY){
		if(map[temp_x][temp_y] == BOARD){
			// change delta despite board's position
			if(temp_y <= current_board+2 ){
				dx *= -1;
				if(dy == 0)
					dy = -1;
			}else if(temp_y > current_board+2 && temp_y <= current_board+4){
				dx *= -1;
				dy = 0;
			}else if(temp_y > current_board+4 && temp_y <= current_board+7){
				dx *= -1;
				if(dy == 0)
					dy = 1;
			}

		} else if(map[temp_x][temp_y] == WALL || map[temp_x][temp_y] == WALL_BOTTOM){
			if(temp_y == 0 || temp_y == MAP_WIDTH-1){	// meet right, left wall
				dy *= -1;
			}else if(temp_x == 0 || temp_y == MAP_HEIGHT-1){// meet up, down wall
				dx *= -1;
			}
			else if(temp_x <= 0 && temp_y <= 0){// meet left edge
				dx *= -1;
				dy *= -1;
			}
			else if(temp_x <= 0 && temp_y <= MAP_WIDTH-1){// meet right edge
				dx *= -1;
				dy *= -1;
			}

			deleteBrick(what, dx, dy);
		}else{									// meet bricks
			deleteBrick(what, dx, dy);
			dx *= -1;	
		}	
	}
}
