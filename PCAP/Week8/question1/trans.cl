__kernel void mat(__global char* A, __global char* B){
	int id = get_global_id(0);
	int ls = get_global_size(0); 
	int pos = 0 ; 
	for( int i = 0 ; i < ls ; i++ )
	{
		if ((int)A[id] > (int)A[i] || (A[id] == A[i] && id < i)) 
		{ 
			pos = pos + 1 ;
		}
		 
	}
	B[pos] = A[id];
}
