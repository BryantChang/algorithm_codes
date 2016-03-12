#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "arr_ops.h"
#define MAX_SIZE 10000
int x[MAX_SIZE], y[MAX_SIZE];
//read the file to init the array
int input(char *filename){
	char line[256];
	int i = 0;
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("cannot open the file\n");
		exit(-1);
	}
	while(fgets(line, 256, fp)) {
		//skip the statement
		if(line[0] == '#') {
			continue;
		}else {
			sscanf(line, "%d,%d", &x[i], &y[i]);
		}
		i++;
	}
	return i;
}

//--------------------------------------------  
//将对arr[left]至arr[right]之间的数进行冒泡排序  
//return:排序后的数组  
//--------------------------------------------
void bubble_sort(int arr[], int left, int right) {
	int i, j;
	for(i = left; i < left + right; i++) {
		for(j = i + i; j <= right; j++) {
			if(arr[i] > arr[j]){
				swap_int(&arr[i], &arr[j]);
			}
		}
	}
}

//--------------------------------------------  
//以值pivot为基准将数组arr中arr[left]到arr[right]为两部分  
//return:基准的下标   
//--------------------------------------------  
int partition(int arr[], int left, int right, int pivot)  
{  
    int i = left - 1;  
    int j = right + 1;  
    while(1){       
        while (arr[++i] < pivot && i <= right);             
        while (arr[--j] > pivot);  
        if (i >= j) break;  
        swap_int(&arr[i], &arr[j]);  
    }  
    return j;  
}


//--------------------------------------------  
//将数组arr分组排序，并将中位数交换到arr的前面  
//--------------------------------------------  
void group_sort(int arr[], int left, int right) {
	int i;
	for(i = 0; i < (right - left + 1) / 5; i++) {
		int p_left = left + 5 * i;
		int p_right = p_left + 4;
		bubble_sort(arr, p_left, p_right);
		swap_int(&arr[left + i], &arr[p_left + 2]);
	}
}

//--------------------------------------------  
//选择数组arr中arr[left]到arr[right]中第serial小的元素,线性时间选择算法  
//return:数组arr中arr[left]到arr[right]中第serial小的元素值  
//--------------------------------------------  
int select_pos(int arr[], int left, int right, int serial) {
	if(right - left < 5) {
		bubble_sort(arr, left, right);
		return arr[left + serial - 1];
	}
	group_sort(arr, left, right);//将数组arr分组排序，并将中位数交换到arr的前面
	int pivot = select_pos(arr, left, left + (right - left + 1)/5 - 1, (right - left + 6)/10); 
	int bound = partition(arr, left, right, pivot);  
                                             //以pviot为基准二分arr  
    int numFront = bound - left + 1;         //计算以bound分界的前半区的个数  
    if (serial <= numFront)   
        return select_pos(arr, left, bound, serial);  
    else   
        return select_pos(arr, bound + 1, right, serial-numFront); 
}

//--------------------------------------------  
//计算数组coordinate中各数到mid的距离和  
//return:距离和  
//-------------------------------------------- 
int get_min_sum_distance(int arr[], int size, int mid) {
	int sum = 0;
	int i;
	for(i = 0; i < size; i++) {
		sum += abs(arr[i] - mid);
	}
	return sum;
}


void usage() {
	printf("Usage: ./postoffice filename\n");
}

int main(int argc, char *argv[]){
	char filename[256];
	if(argc < 2) {
		usage();
		exit(-1);
	}
	strcpy(filename, argv[1]);
	int num_resident = input(filename);
	int i;
	printf("the array of point is:\n");
	for(i = 0; i < num_resident; i++) {
		printf("(%d, %d)", x[i], y[i]);
	}
	printf("\n");
	int min_distance;
	int min_x = select_pos(x, 0, num_resident - 1, (num_resident + 1) / 2);
	int min_y = select_pos(y, 0, num_resident - 1, (num_resident + 1) / 2);
	min_distance = get_min_sum_distance(x, num_resident, min_x) + get_min_sum_distance(y, num_resident, min_y);
	printf("the best postoffice position is (%d, %d)\n", min_x, min_y);
	printf("the min distance is %d\n", min_distance);
	return 0;
}