#include"yasuo.h"

void Show(int *a)
{
	int i;
	for(i=0;a[i]!=-1;i++)
		printf("%d",a[i]);
}

void Select(HuffmanTree HT,int n,int &s1,int &s2)//ѡ��û�и�ĸ�����Ȩֵ��С��������
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
	if(!cd) printf("�ڴ�ռ䲻�㣬��̬�����ڴ�ʧ��!\n");
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	HC=(HuffmanCode)malloc((n+1)*sizeof(int*));
	if(!HC) printf("�ڴ�ռ䲻�㣬��̬�����ڴ�ʧ��!\n");
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
	printf("��������%d���ַ�\n",n);
	
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

void YaSuo(FILE *fpRead)//ѹ������
{
	int i,j,k,jk,flag,number=0,ch,shu,counter,temp,cn=0,s,du=0;
    int a[200],b[200];//a������ַ���asciiֵ,b������ַ��ĳ���Ƶ��
	double a1,a2,ys;//ѹ����
	unsigned char pos;//ѹ����ʱ�򻺴�
	HuffmanTree HT;
	HuffmanCode HC;  
	FILE *fp=fopen("yasuo.huf", "wb");
    if(fpRead==NULL)  
    {  
		printf("���ļ�ʧ��!\n");
        exit(0); 
    }
	if(fp==NULL)
	{
		printf("�����ļ�ʧ��!\n");
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
	printf("�ַ� ASCIIֵ Ƶ�� ����������\n");
	for(i=0;i<number;i++)
	{
		if(a[i]==10) {printf("���з�  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else if(a[i]==13) {printf("��λ��  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else if(a[i]==32) {printf("�ո��  %d    %d     ",a[i],b[i]);Show(HC[i+1]);printf("\n");}
		else {printf("%c      %d    %d     ",a[i],a[i],b[i]);Show(HC[i+1]);printf("\n");}
	}

	//ѹ��
	counter=0;
	
	
	//ͳ�Ʊ���λ��
	pos=pos&0;
	shu=0;//��8��ʱ��д��pos
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
			counter++;//ͳ�Ʊ���λ��
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
	printf("ѹ���ɹ���������ѹ���ļ�yasuo.huf,ѹ����Ϊ%.2f%%\n",ys);

	printf("���ļ��Ĺ���������Ϊ:\n");
	//д��ͷ����Ϣ
	fwrite(&number,sizeof(unsigned char),1,fp);
	temp=counter;
	while(1)
	{
		temp=temp/10;
		cn++;
		if(temp==0) break;
	}
	fwrite(&cn,sizeof(unsigned char),1,fp);//��counter�м�λ
	temp=counter;
	for(i=1;i<=cn;i++)//��counter��λ��˳�����ɵ�λ����λ
	{
		s=temp%10;
		fwrite(&s,sizeof(unsigned char),1,fp);
		temp=(temp-s)/10;
	}

	for(i=1;i<=2*number-1;i++)//���������
	{
		fwrite(&HT[i].weight,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].parent,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].lchild,sizeof(unsigned char),1,fp);
		fwrite(&HT[i].rchild,sizeof(unsigned char),1,fp);
	}
	for(i=0;i<number;i++)//��asciiֵ
	{
		fwrite(&a[i],sizeof(unsigned char),1,fp);
	}


	pos=pos&0;
	shu=0;//��8��ʱ��д��pos
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
			counter++;//ͳ�Ʊ���λ��
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