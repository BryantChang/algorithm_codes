#include <stdio.h>
#include <stdlib.h>
#include "arr_ops.h"
void print_arr_int(int r[], int size, int width){
	int index;
	for(index = 0; index < size; index++) {
		printf("%d    ", r[index]);
		if(((index + 1) % width) == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

void print_arr_float(float r[], int size, int width){
	int index;
	for(index = 0; index < size; index++) {
		printf("%0.2f    ", r[index]);
		if(((index + 1) % width) == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

void print_arr_double(double r[], int size, int width){
	int index;
	for(index = 0; index < size; index++) {
		printf("%0.2lf    ", r[index]);
		if(((index + 1) % width) == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

void swap_arr_int(int r[], int i, int j) {
	int tmp;
	tmp = r[i];
	r[i] = r[j];
	r[j] = tmp;
}


void swap_arr_float(float r[], int i, int j) {
	float tmp;
	tmp = r[i];
	r[i] = r[j];
	r[j] = tmp;
}

void swap_arr_double(double r[], int i, int j) {
	double tmp;
	tmp = r[i];
	r[i] = r[j];
	r[j] = tmp;
}

void swap_int(int *a, int *b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_float(float *a, float *b) {
	float tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void swap_double(double *a, double *b) {
	double tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}