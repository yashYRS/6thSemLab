__kernel void convert (__global int *A , __global int *Res) {
	int thd_id  = get_global_id(0);   
	int temp = A[thd_id] ;
	int num = 0 , pow = 1 , rem ; 
	while ( temp > 0 ) {
		rem = temp%8 ; 
		temp = temp/8 ;
		num = num + pow*rem ;  
		pow = pow*10 ; 
	}
	Res[thd_id] = num ;  
}