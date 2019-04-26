#include"yasuo.h"

void Check()
{
	int flag=1;
	FILE *f1,*f2;
	char ch1,ch2;
	char name1[20];
	char name2[20];
	
	printf("请输入第一个文件名:");
	gets(name1);

	fflush(stdin);
	printf("请输入第二个文件名:");
	gets(name2);
	
	
	f1=fopen(name1,"r");
	if(f1==NULL)
	{
		printf("第一个文件打开失败!\n");
		exit(0);
	}
	f2=fopen(name2,"r");
	if(f2==NULL)
	{
		printf("第二个文件打开失败!\n");
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
		printf("两文件相同!\n");
	}
	else
	{
		printf("两文件不同!\n");
	}
}

	
