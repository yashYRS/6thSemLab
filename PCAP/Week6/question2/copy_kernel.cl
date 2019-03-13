__kernel void copy(__global char *A,__global char *B,__global int *len)
{
	int i=get_global_id(0);
	int j;
	for(j=0,i*=(*len);j<(*len);j++,i++)
		B[i]=A[j];
}
