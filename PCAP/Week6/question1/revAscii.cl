__kernel void rev_ascii (__global char *A,__global char *C) {
	int i  = get_global_id(0); 
	C[i]=0; 
	int tmp; 
	while ( A[i]!= 0 ) {
		tmp = A[i] % 10 ; 
		A[i] = A[i] / 10 ;
		C[i] = C[i]*10 + tmp; ;  
	}
	 
}