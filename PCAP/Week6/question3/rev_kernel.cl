__kernel void reverse(__global char *A,__global int *len)
{
	int i=get_global_id(0);
	char ch=A[i];
	A[i]=A[*len-i-2];
	A[*len-i-2]=ch;
}