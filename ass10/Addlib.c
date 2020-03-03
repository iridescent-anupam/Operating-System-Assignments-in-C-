int *addingTwoArray(int A[],int B[],int n)
{
	int i=0;
	for(i=0;i<n;i++)
	{
		A[i]+=B[i];
	}
	return A;
}
