#include"yasuo.h"

int main()  
{  
	
	int flag;
	char c;
	char jyname[20];
	char ysname[20];
	while(c!='N'&&c!='n')
	{
		Menu();
		scanf("%d",&flag);
		fflush(stdin);
		if(flag==1)
		{
			printf("������Ҫѹ�����ļ���:");		
			gets(ysname);
			FILE *fpRead=fopen(ysname,"r");  
			YaSuo(fpRead);	
		
		}
		else if(flag==2)
		{
			printf("������Ҫ��ѹ���ļ���:");
			gets(jyname);
			FILE *fpjy=fopen(jyname, "rb");
			JieYa(fpjy);	
		}
		else if(flag==3)
		{
			Check();
		}
		else if(flag==4)
		{
			exit(0);
		}
		printf("�Ƿ�Ҫ����ʹ��Y/N?\n");
		c=getchar();
	}
	
   

	return 0;
}