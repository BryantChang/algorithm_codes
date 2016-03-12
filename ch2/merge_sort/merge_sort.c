#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
#define SIZE 10

//将两个有序的子数组合并成归并为一个数组
void merge(int a[], int left, int mid, int right){
	int *b = (int*)malloc((right - left + 1) * sizeof(int));
	int i = left,j = mid + 1,p = 0;
	int r1;
	//两个序列中取小者输出到b[p]
	while(i <= mid && j <= right) {
		if(a[i] < a[j]) {
			b[p++] = a[i++];
		}else {
			b[p++] = a[j++];
		}
	}
	//复制剩余子数组
	while(i <= mid) {
		b[p++] = a[i++];
	}
	while(j <= right) {
		b[p++] = a[j++];
	}
	//将处理完的结果复制回原数组
	for(p = 0, i = left;i <= right;p++,i++) {
		a[i] = b[p];
	}
}

void merge_sort(int a[], int left, int right) {
	if(left < right) {
		int mid = (left + right) / 2;
		merge_sort(a, left, mid);
		merge_sort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}

int main(int argc, char *argv[]){
	int left, right;
	int i;
	int arr[SIZE];
	for(i = 0; i < SIZE; i++) {
		arr[i] = SIZE - i;
	}
	printf("before:\n");
	print_arr_int(arr, SIZE, 10);
	left = 0;
	right = SIZE - 1;
	merge_sort(arr, left, right);
	printf("after\n");
	print_arr_int(arr, SIZE, 10);
	return 0;
}