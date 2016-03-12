#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define NUM 3

void perm1(int r[], int i, int n) {
	int index;
	int j;
	if(i == n) {
		print_arr_int(r, n, 10);
	}else {
		for(j = i; j < n; j++) {
			swap_arr_int(r, i, j);
			perm1(r, i + 1, n);
			swap_arr_int(r, i, j);
		}
	}
}

int main(int argc, char *argv[]){
	int r[NUM];
	int i;
	for(i = 0; i < NUM; i++) {
		r[i] = i;
	}
	perm1(r, 0, NUM);
	return 0;
}