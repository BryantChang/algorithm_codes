#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
typedef struct{
  char ch;
  float weight;
  int lchild,rchild,parent;
}hufmtree;
typedef struct{
  int len;
  char bits[MAX_LINE];   //位串
	int start;      //编码在位串中的起始位置
 	char ch;        //字符
}codetype;
typedef struct{
  char ch;
  int count;
}word_count;



void huffman(int node_num, int word_num, word_count *wc, hufmtree *tree) {
  int i,j,p1,p2;//p1,p2分别记住每次合并时权值最小和次小的两个根结点的下标
 	float small1,small2,f;
 	char c;
 	for(i=0;i<node_num;i++) {
    tree[i].parent = 0;
    tree[i].lchild = -1;
    tree[i].rchild = -1;
    tree[i].weight = 0.0;
 	}

  for(i = 0;i < word_num;i++) {
    tree[i].ch = wc[i].ch;
    tree[i].weight = wc[i].count*1.0;
  }
  for(i = word_num; i < node_num; i++) {
    p1 = p2 = 0;
    small1 = small2 = maxval;
    for(j = 0; j < i; j++) {
      if(tree[j].parent == 0) {
        if(tree[j].weight < small1){
          small2 = small1;  //改变最小权、次小权及对应的位置
          small1 = tree[j].weight;
          p2=p1;
          p1=j;
        }else{
          if(tree[j].weight<small2) {
            small2=tree[j].weight;  //改变次小权及位置
            p2=j;
          }
        }
      }
    }
    tree[p1].parent=i;
    tree[p2].parent=i;
    tree[i].lchild=p1;  //最小权根结点是新结点的左孩子
    tree[i].rchild=p2;  //次小权根结点是新结点的右孩子
    tree[i].weight=tree[p1].weight+tree[p2].weight;
  }
}

//根据哈夫曼树求出哈夫曼编码
void huffmancode(int word_num, codetype *code, hufmtree *tree){
  int i, c, p;
  codetype cd;
  int len = 0;
  for(i = 0; i < word_num; i++) {
    len = 0;
    cd.start = word_num;
    cd.ch = tree[i].ch;
    c = i;
    p = tree[i].parent;
    while(p!=0){
      cd.start--;
      if(tree[p].lchild == c) {
        len++;
        cd.bits[cd.start] = '0';
      }else {
        len++;
        cd.bits[cd.start] = '1';
      }
      c = p;
      p = tree[p].parent;
    }
    code[i] = cd;
    code[i].len = len;
  }
  
}


int read_file(word_count *wc, char *file_name){
  char sz_buffer[MAX_LINE];
  int k = 0;
  int i,j;
  int cur_len = 0;
  int found = 0;
  FILE* fp = fopen(file_name, "r");
  if(fp != NULL) {
    while(fgets(sz_buffer, MAX_LINE, fp)!=NULL){
      for(i = 0; i < strlen(sz_buffer); i++){
        found = 0;
        for(j = 0; j < cur_len; j++) {
          if(sz_buffer[i] == wc[j].ch) {
            wc[j].count++;
            found = 1;
          }else{
            continue;
          }
        }
        if(!found) {
          wc[cur_len].ch = sz_buffer[i];
          wc[cur_len].count = 1;
          cur_len++;
        }
      }
    }
  }else{
    printf("open file failed\n");
    exit(-1);
  }
  fclose(fp);
  return cur_len;
}

void write_code(int word_num, codetype *code){
  char file_name[256] = "code.txt";
  FILE* fp = fopen(file_name, "w");
  int i,j,m;
  fprintf(fp, "the code is as followed\n");
  char *bits = (char*)malloc(word_num*sizeof(char));
  int ii = 0;
  for(i = 0; i < word_num; i++) {
    ii = 0;
    for(m = code[i].start; m < word_num; m++) {
      bits[ii] = code[i].bits[m];
      ii++;
    }
    bits[ii] = "\0";
    fprintf(fp, "%c:%s", code[i].ch, bits);
  }
  fclose(fp);
}

void write_compress(char *src_file_name, char *des_file_name, codetype *code, int word_num) {
  char sz_buffer[MAX_LINE];
  int k = 0;
  int i,j,m;
  int cur_len = 0;
  int found = 0;
  FILE* fp = fopen(src_file_name, "r");
  FILE* fp_out = fopen(des_file_name, "wb+");
  if(fp != NULL) {
    while(fgets(sz_buffer, MAX_LINE, fp)!=NULL){
      for(i = 0; i < strlen(sz_buffer); i++){
        for(j = 0; j < word_num; j++){
          if(sz_buffer[i] == code[j].ch) {
            for(m = code[j].start; m < word_num; m++) {
              //printf("%d\n", sizeof(code[j].bits[m]));
              fwrite(&code[j].bits[m], sizeof(char), 1, fp_out);
            }
          }
        }
      }
    }
  }else{
    printf("open file failed\n");
    exit(-1);
  }
  fclose(fp);
  fclose(fp_out);
}

void usage(){
  printf("usage:./huffman_tree source file des file\n");
}

void write_word_count(int word_num, word_count *wc){
  char file_name[256] = "word_count.txt";
  FILE* fp = fopen(file_name, "w");
  int i;
  fprintf(fp, "the word_count is as followed\n");
  for(i = 0; i < word_num; i++) {
    fprintf(fp, "%c:%d\n", wc[i].ch, wc[i].count);
  }
  fclose(fp);
}

int main(int argc, char **argv){
	if(argc < 3){
    usage();
    exit(-1);
  }
  char src_file_name[256];
  char des_file_name[256];
  strcpy(src_file_name, argv[1]);
  strcpy(des_file_name, argv[2]);
  word_count *wc;
  wc = (word_count*)malloc(MAX_LINE * sizeof(word_count));
  int word_num;
  int node_num;
  word_num = read_file(wc, src_file_name);

  int m;
  node_num = 2 * word_num - 1;
 	hufmtree *tree;
  tree = (hufmtree*)malloc(node_num*sizeof(hufmtree));
  codetype *code;
  code = (codetype*)malloc(word_num*sizeof(codetype));
 	int i,j;//循环变量
 	huffman(node_num, word_num, wc, tree);//建立哈夫曼树
 	huffmancode(word_num, code, tree);//根据哈夫曼树求出哈夫曼编码
 	printf("writting the word count\n");
  write_word_count(word_num, wc);
  printf("writting the huffman_code\n");
  write_code(word_num, code);
  printf("write_compress\n");
  write_compress(src_file_name, des_file_name, code, word_num);
 	return 0;
}