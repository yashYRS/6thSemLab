__kernel void EvenOdd(__global int *A) {
	int id = get_global_id(0) ; 
	int size = get_global_size(0) ;
	int temp ;  
	if ( (id%2)==0 && id < size -1 ) 
	{
		if ( A[id] >= A[id+1] ) 
		{
			temp = A[id] ; 
			A[id] = A[id+1] ; 
			A[id + 1] = temp ; 
		} 
	}
}