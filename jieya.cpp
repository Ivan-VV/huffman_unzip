#include"yasuo.h"

void JieYa(FILE *fpjy)//��ѹ����
{
	int i,j,k,number=0,ch,counter,jy=0,cn=0,cheng;
    int c[200];//c�����ǽ�ѹʱ���ļ��ڱ���
	unsigned char pos;//��ѹ��ʱ�򻺴�
	HuffmanTree HT;
   


	//��ѹ��
	FILE *fjy=fopen("jieya.txt","w");
	if(fpjy==NULL)  
    {  
		printf("���ļ�ʧ��!\n");
        exit(0); 
    }
	if(fjy==NULL)
	{
		printf("�����ļ�ʧ��!\n");
		exit(0);
	}
	printf("\n��ѹ�ɹ�!������Ŀ���ļ�jieya.txt!\n");
	printf("��ѹ���ļ�ԭ��Ϊ:\n");
	ch=fgetc(fpjy);//��ȡ�ַ���������
	number=ch;
	ch=fgetc(fpjy);//��ȡ����λ����
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
	for(i=1;i<=2*number-1;i++)//��ȡ��������
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
	}//��ȡͷ����Ϣ


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
				fprintf(fjy,"%c",c[j-1]);//���ɽ�ѹ�ļ�
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