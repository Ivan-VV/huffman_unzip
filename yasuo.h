#include<stdio.h>  
#include<stdlib.h>
#include<string.h>

typedef struct HTNode{
	int weight;/*记录权重*/ 
    int parent;/*记录双亲*/ 
    int lchild;/*左右子树*/ 
    int rchild;   
}HTNode,*HuffmanTree;
typedef int **HuffmanCode;

void Menu();
void YaSuo(FILE *fpRead);
void JieYa(FILE *fpjy);
void Check();