#include"yasuo.h"

void Show(int *a)
{
	int i;
	for(i=0;a[i]!=-1;i++)
		printf("%d",a[i]);
}

void Select(HuffmanTree HT,int n,int &s1,int &s2)//选择没有父母结点且权值最小的两棵树
{
	int i,min1=-1,min2=-2;
	for(i=1;i<=n;i++)
	{
		if(HT[i].parent!=0) continue;
		if(min1==-1) {min1=i;continue;}
		if(min2==-1) {min2=i;continue;}
		if((HT[i].weight<HT[min1].weight)&&(HT[min1].weight>=HT[min2].weight)) min1=i;
		else if((HT[i].weight<HT[min2].weight)&&(HT[min2].weight>=HT[min1].weight)) min2=i;
	}
	s1=min1;
	s2=min2;
}



void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	int start,c,f,m,i,j,s1,s2,shu;
	int *cd;
	HuffmanTree p;
	if(n<=1) return;
	m=2*n-1;
	cd=(int*)malloc(n*sizeof(int));
	if(!cd) printf("内存空间不足，动态分配内存失败!\n");
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	HC=(HuffmanCode)malloc((n+1)*sizeof(int*));
	if(!HC) printf("内存空间不足，动态分配内存失败!\n");
	p=HT;
	for(i=1;i<=n;++i,++w) 
	{
		p[i].weight=*w;
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}
	for(i;i<=m;++i) 
	{
		p[i].weight=0;
		p[i].parent=0;
		p[i].lchild=0;
		p[i].rchild=0;
	}
	for(i=n+1;i<=m;++i)
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	printf("共出现了%d种字符\n",n);
	
	cd[n-1]=-1;
	for(i=1;i<=n;i++)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
		{
			if(HT[f].lchild==c) cd[--start]=0;
			else cd[--start]=1;
		}
		HC[i]=(int*)malloc((n-start)*sizeof(int));
		shu=n-start;
		for(j=0;j<shu;j++,start++)
		{
			HC[i][j]=cd[start];
		}
	}	
	free(cd);
}

void YaSuo(FILE *fpRead)//压缩函数
{
	int i,j,k,jk,flag,number=0,ch,shu,counter,temp,cn=0,s,du=0;
    int a[200],b[200];//a数组存字符的ascii值,b数组存字符的出现频率
	double a1,a2,ys;//压缩率
	unsigned char pos;//压缩的时候缓存
	HuffmanTree HT;
	HuffmanCode HC;  
	FILE *fp=fopen("yasuo.huf", "wb");
    if(fpRead==NULL)  
    {  
		printf("打开文件失败!\n");
        exit(0); 
    }
	if(fp==NULL)
	{
		printf("创建文件失败!\n");
		exit(0);
	}
    for(i=0;i<100;i++)
		a[i]=-1,b[i]=0;
	i=0;
    while(feof(fpRead)==0)
	{
		flag=1;
		ch=fgetc(fpRead);
		du++;
		for(j=0;j<i;j++)
		{
			if(a[j]==ch) {flag=0;b[j]++;break;}
		}
		if(flag==1)
		{
			a[i]=ch;
			b[i]++;
			i++;
			number++;
		}
	}
	
	number--;


	HuffmanCoding(HT,HC,b,number);
	printf("字符 ASCII值 频率 哈夫曼编码\n");
	for(i=0;i<number;i++)
	{
		if(a[i]==10) {printf("换行符  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else if(a[i]==13) {printf("归位键  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else if(a[i]==32) {printf("空格符  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else {printf("%c      %d    %d     ",a[i],a[i],b[i]);Show(HC[i+1]);printf("\n");}
	}

	//压缩
	counter=0;
	
	
	//统计比特位数
	pos=pos&0;
	shu=0;//满8的时候写入pos
	rewind(fpRead);
	while(feof(fpRead)==0)
	{
		ch=fgetc(fpRead);
		flag=0;
		for(j=0;j<number;j++)
		{
			if(a[j]==ch) {flag=1;break;}
		}
		if(flag==0) continue;
		for(k=0;HC[j+1][k]!=-1;k++)
		{			
		}
		k--;
		for(jk=0;jk<=k;jk++)
		{
			pos=pos*2;
			pos=pos+HC[j+1][jk];	
			shu++;
			counter++;//统计比特位数
			if(shu==8)
			{
				pos=pos&0;
				shu=0;
			}
		}	
	}
	

	du=du*8;
	a1=counter;
	a2=du;
	ys=a1/a2;
	ys=ys*100;
	printf("压缩成功，已生成压缩文件yasuo.huf,压缩率为%.2f%%\n",ys);

	printf("该文件的哈夫曼编码为:\n");
	//写入头部信息
	fwrite(&number,sizeof(unsigned char),1,fp);
	temp=counter;
	while(1)
	{
		temp=temp/10;
		cn++;
		if(temp==0) break;
	}
	fwrite(&cn,sizeof(unsigned char),1,fp);//存counter有几位
	temp=counter;
	for(i=1;i<=cn;i++)//存counter各位，顺序是由低位到高位
	{
		s=temp%10;
		fwrite(&s,sizeof(unsigned char),1,fp);
		temp=(temp-s)/10;
	}

	for(i=1;i<=2*number-1;i++)//存哈夫曼树
	{
		fwrite(&HT[i].weight,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].parent,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].lchild,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].rchild,sizeof(unsigned char),1,fp);
	}
	for(i=0;i<number;i++)//存ascii值
	{
		fwrite(&a[i],sizeof(unsigned char),1,fp);
	}


	pos=pos&0;
	shu=0;//满8的时候写入pos
	rewind(fpRead);
	while(feof(fpRead)==0)
	{
		ch=fgetc(fpRead);
		flag=0;
		for(j=0;j<number;j++)
		{
			if(a[j]==ch) {flag=1;break;}
		}
		if(flag==0) continue;
		Show(HC[j+1]);
		for(k=0;HC[j+1][k]!=-1;k++)
		{			
		}
		k--;
		for(jk=0;jk<=k;jk++)
		{
			pos=pos*2;
			pos=pos+HC[j+1][jk];	
			shu++;
			counter++;//统计比特位数
			if(shu==8)
			{
				fwrite(&pos,sizeof(unsigned char),1,fp);
				pos=pos&0;
				shu=0;
			}
		}	
	}
	if(shu!=0)
	{
		for(i=1;i<=8-shu;i++)
			pos=pos*2;
		fwrite(&pos,sizeof(unsigned char),1,fp);
	}

	
	printf("\n\n\n");
	
	


	fclose(fpRead);
	fclose(fp);
}