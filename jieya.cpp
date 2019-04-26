#include"yasuo.h"

void JieYa(FILE *fpjy)//解压函数
{
	int i,j,k,number=0,ch,counter,jy=0,cn=0,cheng;
    int c[200];//c数组是解压时读文件内编码
	unsigned char pos;//解压的时候缓存
	HuffmanTree HT;
   


	//解压缩
	FILE *fjy=fopen("jieya.txt","w");
	if(fpjy==NULL)  
    {  
		printf("打开文件失败!\n");
        exit(0); 
    }
	if(fjy==NULL)
	{
		printf("创建文件失败!\n");
		exit(0);
	}
	printf("\n解压成功!已生成目标文件jieya.txt!\n");
	printf("该压缩文件原文为:\n");
	ch=fgetc(fpjy);//读取字符种类数量
	number=ch;
	ch=fgetc(fpjy);//读取比特位数量
	cn=ch;

	counter=0;
	cheng=1;	
	for(i=1;i<=cn;i++)
	{
		ch=fgetc(fpjy);
		counter=counter+ch*cheng;
		cheng=cheng*10;
	}

	HT=(HuffmanTree)malloc((2*number)*sizeof(HTNode));
	for(i=1;i<=2*number-1;i++)//读取哈夫曼树
	{
		ch=fgetc(fpjy);
		HT[i].weight=ch;
		ch=fgetc(fpjy);
		HT[i].parent=ch;
		ch=fgetc(fpjy);
		HT[i].lchild=ch;
		ch=fgetc(fpjy);
		HT[i].rchild=ch;
	}
	for(i=0;i<number;i++)
	{
		ch=fgetc(fpjy);
		c[i]=ch;
	}//读取头部信息


	j=2*number-1;
	while(1)
	{
		ch=fgetc(fpjy);
		for(i=0;i<=7;i++)
		{
			pos=ch;
			for(k=1;k<=i;k++)
				pos=pos*2;
			for(k=1;k<=7;k++)
				pos=pos/2;

			if(pos==1) j=HT[j].rchild;
			else if(pos==0) j=HT[j].lchild;
			if((HT[j].rchild==0)&&(HT[j].lchild==0))
			{
				printf("%c",c[j-1]);
				fprintf(fjy,"%c",c[j-1]);//生成解压文件
				j=2*number-1;
			}
			jy++;
			if(jy==counter) break;
		}
		if(jy==counter) break;
	}

		
	printf("\n");

	fclose(fpjy);
	fclose(fjy);
}