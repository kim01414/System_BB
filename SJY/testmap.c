void test1(){
	int i, j;

	for(i=4; i<BRICK_HEIGHT; i+=2) {
		for(j=7; j<8; j++){
			map[i][j]=BRICK3;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=8; j<9; j++) {
			map[i][j]=BRICK2;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=9; j<10; j++) {
			map[i][j]=BRICK1;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=10; j<11; j++) {
			map[i][j]=BRICKE;
			brick_left+=2;
			if(j%4==1) j++;
		}
		for(j=11; j<12; j++) {
			map[i][j]=BRICKU;
			brick_left+=2;
			if(j%4==1) j++;
		}
	}
}
