#include<stdio.h>  
#include<stdlib.h>
#include<string.h>

typedef struct HTNode{
	int weight;/*��¼Ȩ��*/ 
    int parent;/*��¼˫��*/ 
    int lchild;/*��������*/ 
    int rchild;   
}HTNode,*HuffmanTree;
typedef int **HuffmanCode;

void Menu();
void YaSuo(FILE *fpRead);
void JieYa(FILE *fpjy);
void Check();