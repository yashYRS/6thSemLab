__kernel void vector_add (__global int *A , __global int *Res) {
	int i  = get_global_id(0);
	int *rem, *pow , *res ;  
	pow[i] = 1; 
	while ( A[i] >= 0)  {
		rem[i] = A[i]%8 ;
		A[i] = A[i]/8 ;  
		res[i] = res[i] + pow[i]*rem[i] ; 
		pow[i] = 10 *pow[i] ;  
	}
	Res[i] = res[i] ; 
}
