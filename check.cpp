#include"yasuo.h"

void Check()
{
	int flag=1;
	FILE *f1,*f2;
	char ch1,ch2;
	char name1[20];
	char name2[20];
	
	printf("�������һ���ļ���:");
	gets(name1);

	fflush(stdin);
	printf("������ڶ����ļ���:");
	gets(name2);
	
	
	f1=fopen(name1,"r");
	if(f1==NULL)
	{
		printf("��һ���ļ���ʧ��!\n");
		exit(0);
	}
	f2=fopen(name2,"r");
	if(f2==NULL)
	{
		printf("�ڶ����ļ���ʧ��!\n");
		exit(0);
	}

	while(1)
	{
		ch1=fgetc(f1);
		ch2=fgetc(f2);
		if(ch1!=ch2)
		{
			flag=0;
			break;
		}
		if((feof(f1)==0)&&(feof(f2)!=0))
		{
			flag=0;
			break;
		}
		if((feof(f2)==0)&&(feof(f1)!=0))
		{
			flag=0;
			break;
		}
		if((feof(f1)!=0)&&(feof(f2)!=0))
		{
			break;
		}
	}
	
	if(flag==1)
	{
		printf("���ļ���ͬ!\n");
	}
	else
	{
		printf("���ļ���ͬ!\n");
	}
}

	
