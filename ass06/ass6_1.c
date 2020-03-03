#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<math.h>
#include<unistd.h>

int main()
{
	srand(time(0));
	int i,j,x;
	int Lottery[]={7,15,29,34,45,51,66,78,83,100};
	int Run[10]={0};
	for(i=0;i<100;i++)
	{
		int r=rand()%100;
		for(j=0;j<10;j++)
		{
			if(Lottery[j]>r)
			{
				Run[j]++;
				break;
			}
		}	
			if(i==25||i==50)
			{
				if(i==25)
				{
					printf("After 25 iterations : ");
					for(x=0;x<=9;x++)
					{
						printf("%d ",Run[x]);
					}
				}	
				else		
				{
					printf("\nAfter 50 iterations : ");
					for(x=0;x<=9;x++)
					{
						printf("%d ",Run[x]);
					}
				}
			}
		
	}
	printf("\n");
	return 0;
}				
