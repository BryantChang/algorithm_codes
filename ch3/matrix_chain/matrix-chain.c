#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define MAT_NUM 6
int m[MAT_NUM+1][MAT_NUM+1];
int s[MAT_NUM+1][MAT_NUM+1];
int p[MAT_NUM+1];
void matrix_chain(int p[], int m[][MAT_NUM+1], int s[][MAT_NUM+1]) {
	int i, r, j, k, t;
	for(i = 1; i <= MAT_NUM; i++) m[i][i] = 0;//对角线为0
	for(r = 2; r <= MAT_NUM; r++) {//长度从2到n
		for(i = 1; i <= MAT_NUM - r + 1; i++) {
			j = i + r - 1;
			m[i][j] = m[i][i] + m[i+1][j] + p[i-1]*p[i]*p[j];
			s[i][j] = i;

			for(k = i + 1; k < j; k++) {
				t = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
				if(t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}


void print_opt_parents(int s[][MAT_NUM+1], int i, int j) {
	if(i == j) {//头尾一致直接打印
		printf("A%d", i);
	}else {
		printf("(");
		//通过s矩阵找到断点递归显示断点前后
		print_opt_parents(s, i, s[i][j]);
		print_opt_parents(s, s[i][j]+1, j);
		printf(")");
	}
}

int main(int argc, char *argv[]){
	int i,j;
	//initialization
	for(i = 0; i < MAT_NUM+1; i++) {
		p[i] = 0;
		for(j = 0; j < MAT_NUM+1; j++) {
			s[i][j] = 0;
			m[i][j] = 0;
		}
	}
	p[0] = 30;
	p[1] = 35;
	p[2] = 15;
	p[3] = 5;
	p[4] = 10;
	p[5] = 20;
	p[6] = 25;
	matrix_chain(p, m, s);
	printf("the result is:\n");
	print_opt_parents(s, 1, 6);
	printf("\n");
	printf("the min time is %d\n", m[1][6]);
	return 0;
}