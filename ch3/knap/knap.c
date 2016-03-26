#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0

int c[100][100];


int init(int count, char *filename, int *w, int *v) {
	if((!w) || (!v)) {
		return FALSE;
	}
	char line[256];
	int i, j, k, t;
	FILE *fp = fopen(filename, "r");
	if(fp == NULL) {
        printf("cannot open the file\n");
       	return FALSE;
    }
    i = 1;
    while(fgets(line, 256, fp)) {
        //skip the statment
        if(line[0] == '#') {
            continue;
        }else {
            sscanf(line, "%d\t%d", &w[i], &v[i]);
            i++;
        }
    }
    return TRUE;
}

void usage() {
	printf("Usage:./knap filename\n");
}

int knap(int m, int n, int *w, int *v) {
	int i, j;
	for(i=1;i<n+1;i++){
        for(j=1;j<m+1;j++){
	        if(j<w[i]){
	            c[i][j]=c[i-1][j];
	   
	        }else if(c[i-1][j-w[i]]+v[i]>c[i-1][j]){
	            c[i][j]=c[i-1][j-w[i]]+v[i];
	        }else{
	            c[i][j]=c[i-1][j];
	        }
    	}
    }
    return c[n][m];
}

int main(int argc, char *argv[]){
	char ch;
	char filename[256];
	int m,n,i,j;
	//operate the params
	int opt, opt_index = 0;
    while((ch = getopt(argc, argv, "n:m:f:")) != EOF) {
        switch(ch) {
            case 'm':
                m = atoi(optarg);
                break;
            case 'f':
                strcpy(filename, optarg);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            default:
                usage();
                return -1;

        }
    }
    if(m == 0 || n == 0 || !strcmp(filename, "")) {
        usage();
        return -1;
    }
	int *w, *v;
	w = (int*)malloc((n + 1) * sizeof(int));
	v = (int*)malloc((n + 1) * sizeof(int));

	for(i = 0; i < n+1; i++) {
		for(j = 0; j < m+1; j++) {
			c[i][j] = 0;
		}
	}
	int flag = init(n, filename, w, v);
	if(!flag) {
		printf("init error\n");
		exit(-1);
	}
	int max_value;
	max_value = knap(m, n, w, v);
	printf("the max value is %d\n", max_value);
	printf("the array is:\n");
	for(i = 0;i < n+1; i++){
        for(j = 0;j < m+1; j++){
     		printf("%4d",c[i][j]);
   	 	}
   	 	printf("\n");
   	 }

	return 0;
}