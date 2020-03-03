#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	
	FILE *fp;
	fp = fopen("/home/student/Anupam_510817049/Anupam_510817049OS5thSem/Assignment2/ExecutionTimes.csv","w");

	long long int i;
	for (i=0;i<100000;i++)
	{
		struct timeval t;
		gettimeofday(&t,NULL);
		printf("%s ---> %ld : Execution Time\n",argv[1],t.tv_usec);
		fprintf(fp,"%s,%ld\n",argv[1],t.tv_usec);
	}
	fclose(fp);
	return 0;
}	
