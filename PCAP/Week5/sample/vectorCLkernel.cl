__kernel void vector_add (__global int *A , __global int *B, __global int *Res) {
	int thd_id  = get_global_id(0); 
	Res[thd_id] = A[thd_id] + B[thd_id] ; 
}