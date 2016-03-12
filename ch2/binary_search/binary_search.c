#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define NUM 50
int binary_search(int r[], int value, int size) {
	int left = 0;
	int right = size - 1;
	while(left <= right) {
		int middle = (left + right) / 2;
		if(value == r[middle]) {
			return middle;
		}else if(value > middle) {
			left = middle + 1;
		}else {
			right = middle - 1;
		}
	}
	return -1;
}

int main(int argc, char *argv[]){
	int arr[NUM];
	int i;
	int key;
	for(i = 0; i < NUM; i++) {
		arr[i] = i;
	}

	printf("have the value\n");
	key = binary_search(arr, 20, NUM);
	printf("the 20 is key of %d\n", key);
	printf("not have the value\n");
	key = binary_search(arr, 60, NUM);
	printf("the 60 is key of %d\n", key);
	return 0;
}