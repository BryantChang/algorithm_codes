#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_A 30
#define NUM_B 30
int c[NUM_A+1][NUM_B+1];
int lcs_length(char x[], char y[], int b[][NUM_B+1], int m, int n) {
	int i,j;
	for(i = 1; i <= m; i++) c[i][0] = 0;
	for(i = 1; i <=n; i++) c[0][i] = 0;
	for(i = 1; i <= m; i++) {
		for(j = 1; j <= n; j++) {
			if(x[i-1] == y[j-1]) { //xm = yn
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j] = 1;
			}else if(c[i-1][j] >= c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j] = 2;
			}else {
				c[i][j] = c[i][j-1];
				b[i][j] = 3;
			}
		}
	}
	return c[m][n];
}

void lcs(int i, int j, char x[], int b[][NUM_B+1]) {
	if(i == 0||j == 0) return;
	if(b[i][j] == 1) {
		lcs(i-1, j-1, x, b);
		printf("%c",x[i-1]);
	}else if(b[i][j] == 2){
		lcs(i-1, j, x, b);
	}else {
		lcs(i, j-1, x, b);
	}
}

int main(int argc, char *argv[]){
	int b[NUM_A+1][NUM_B+1];
	int i,j;
	for(i = 0; i < NUM_A+1; i++) {
		for(j = 0; j < NUM_B+1; j++) {
			c[i][j] = 0;
			b[i][j] = 0;
		}
	}
	char* x = "abcbdab";
	char* y = "bdcaba";
	int xlen = strlen(x);
	int ylen = strlen(y);
	int len = lcs_length(x, y, b, xlen, ylen);
	printf("%s\n", x);
	printf("the result is:");
	lcs(xlen, ylen, x, b);
	printf("\n");
	printf("the length is %d\n", len);
	printf("\n");
	return 0;
}