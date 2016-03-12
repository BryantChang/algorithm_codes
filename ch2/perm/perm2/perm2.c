#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define NUM 5
void perm2(int r[], int n, int size) {
	int i;
	if(n == 0) {
		print_arr_int(r, size, 10);
	}else {
		for(i = 0; i < size; i++) {
			if(r[i] == 0) {
				r[i] = n;
				perm2(r, n-1, size);
				r[i] = 0;
			}
		}
	}
}
int main(int argc, char **argv){
	int r[NUM];
	int i;
	for(i = 0; i < NUM; i++) {
		r[i] = 0;
	}
	perm2(r, NUM, NUM);
	return 0;
}