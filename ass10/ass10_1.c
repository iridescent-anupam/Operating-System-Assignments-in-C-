#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main()
{
	int A[5],B[5],i=0;
	int *sum;
	void *handler;
	int* (*addArray)(int*,int*,int);

	//Opening the library file.
	handler = dlopen ("./Addlib.so", RTLD_LAZY);

	//getting pointer to the function.
	addArray = dlsym(handler, "addingTwoArray");

	//Accepting arrays.
	printf("Enter two arrays of length 5 each\n");
	for(i=0;i<5;i++)
		scanf("%d",&A[i]);
	for(i=0;i<5;i++)
		scanf("%d",&B[i]);
	
	//calling library function.
	sum=(*addArray)(A,B,5);
	
	//printing Result.
	printf("\nThe addition of two arrays is : ");
	for(i=0;i<5;i++)
		printf("%d  ",sum[i]);
		
	//closing library
	dlclose(handler);
}
