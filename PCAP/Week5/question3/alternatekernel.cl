__kernel void switch_array (__global int *A) {
	int thd_id  = get_global_id(0);
	int temp = A[thd_id] ;  
	if ( thd_id % 2 == 0 ) {
		A[thd_id] = A[thd_id + 1] ; 
		A[thd_id + 1] = temp ; 
	} 
}