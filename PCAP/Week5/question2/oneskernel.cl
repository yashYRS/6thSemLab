__kernel void store_ones (__global int *A , __global int *Res) {
	int thd_id  = get_global_id(0);   
	int temp = A[thd_id] ;
	int num = 0 ; 
	while ( temp > 0 ) {
		temp = temp/10 ; 
		num = num*10 + 1 ; 
	}
	Res[thd_id] = num - A[thd_id] ;
}