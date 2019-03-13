__kernel void reverse(__global char *A,__global int *ind)
{
	int i=get_global_id(0);
	int startI = ind[i];
	int endI = ind[i+1];
	char tempCh; 
	int temp;
	int lenWord = (startI+endI)/2;
	for(temp = startI ; temp < lenWord ; temp++)
	{
		printf("%c",A[temp]);
		tempCh = A[temp]; 	
		A[temp] = A[lenWord-2-temp];
		A[lenWord-2-temp] = tempCh;
	}
}