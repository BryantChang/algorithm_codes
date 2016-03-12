#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define SIZE 10
int quick_sort_pos(int a[], int low, int high){
	int tmp = a[low],i = low,j = high;
	while(i < j) {
		while((a[j] >= tmp) && (i < j)) j--;
		if(i < j){
			swap_int(&a[i], &a[j]);
			i++;
		}
		while((a[i] <= tmp) && (i < j)) i++;
		if(i < j) {
			swap_int(&a[i], &a[j]);
			j--;
		}
	}
	return i;
}

void quick_sort(int a[], int low, int high) {
	int pos;
	if(low < high) {
		pos = quick_sort_pos(a, low, high);
		quick_sort(a, low, pos-1);
		quick_sort(a, pos+1, high);
	}
}

int main(int argc, char *argv[]){
	int arr[SIZE];
	int i;
	for(i = 0; i < SIZE; i++) {
		arr[i] = SIZE - i;
	}
	int low, high;
	low = 0;
	high = SIZE - 1;
	printf("before:\n");
	print_arr_int(arr, SIZE, 10);
	quick_sort(arr, low, high);
	printf("after\n");
	print_arr_int(arr, SIZE, 10);
	return 0;
}