#include <stdio.h>
#include <stdlib.h>
#define CHESS_SIZE 4
#define SIZE 1024
int chess[SIZE][SIZE];
int L_no = 1;
void chess_cover(int tr, int tc, int dr, int dc, int size) {
	if(size == 1) return;
	int t = L_no++; //L型牌的编号
	int s = size / 2;
	//覆盖左上角的棋盘
	if((dr < tr + s) && (dc < tc + s)) {
		chess_cover(tr, tc, dr, dc, s);
	}else {
		chess[tr+s-1][tc+s-1] = t;
		chess_cover(tr, tc, tr+s-1, tc+s-1, s);
	}
	if (dr < tr + s && dc >= tc + s){
		chess_cover(tr, tc+s, dr, dc, s);
	}else {        
		chess[tr + s - 1][tc + s] = t;
      	chess_cover(tr, tc+s, tr+s-1, tc+s, s);
    }
        // 覆盖左下角子棋盘
    if (dr >= tr + s && dc < tc + s){
    	chess_cover(tr+s, tc, dr, dc, s);
    }else {
    	chess[tr + s][tc + s - 1] = t;
    	chess_cover(tr+s, tc, tr+s, tc+s-1, s);
    }
    if (dr >= tr + s && dc >= tc + s){
       chess_cover(tr+s, tc+s, dr, dc, s);
    }else {
       chess[tr + s][tc + s] = t;
       chess_cover(tr+s, tc+s, tr+s, tc+s, s);
   }
}

void usage(){
	printf("Usage ./chess_cover dr, dc\n");
}

void out_of_range() {
	printf("the dr or dc must under %d and over 0\n", CHESS_SIZE);
}

int main(int argc, char *argv[]){
	if(argc < 3) {
		usage();
		return 1;
	}
	int dr, dc;
	dr = atoi(argv[1]);
	dc = atoi(argv[2]);
	if((dr >= CHESS_SIZE) || (dc >= CHESS_SIZE) || (dr < 0) || (dc < 0)){
		out_of_range();
		return 1;
	}
	int i,j;
	chess_cover(0, 0, dr, dc, CHESS_SIZE);
	for(i = 0; i < CHESS_SIZE; i++) {
		for(j = 0; j < CHESS_SIZE; j++) {
			printf("%d  ", chess[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}