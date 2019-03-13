#include<stdio.h>
#include<CL/cl.h>
#include<stdlib.h>
#include<time.h>
#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
	//Create two input vectors
	int i;
	clock_t start , end ;
	start = clock() ;
	int N=1000 ;
	char *A = (char*)malloc(sizeof(char)*N) ;
	char *C = (char*)malloc(sizeof(char)*N) ;
	printf("Enter a string: \n");
	fgets(A,N,stdin) ;

	// Load the kernel source code into the source_str

	FILE *fp ;
	char *source_str ;
	size_t source_size ;
	fp = fopen("revAscii.cl","r") ;
	if(!fp) {
		fprintf(stderr, " Failed to load the kernel \n " ) ;
		getchar() ;
		exit(1) ;
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE) ;
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE , fp) ;
	fclose(fp) ;

	cl_platform_id platform_id = NULL ;
	cl_device_id device_id = NULL ;
	cl_uint ret_num_devices ;
	cl_uint ret_num_platforms ;

	cl_int ret = clGetPlatformIDs(1, &platform_id , &ret_num_platforms) ;
	ret = clGetDeviceIDs(platform_id , CL_DEVICE_TYPE_ALL, 1, &device_id, &ret_num_devices) ;

	cl_context context = clCreateContext(NULL,1, &device_id, NULL, NULL, &ret) ;
	cl_command_queue cmd_q = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret) ;

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, N*sizeof(char), NULL, &ret ) ;
	cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N*sizeof(char), NULL, &ret ) ;

	ret = clEnqueueWriteBuffer(cmd_q, a_mem_obj, CL_TRUE,0, N*sizeof(char), A,0,NULL, NULL) ;

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret) ;
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL , NULL ) ;

	cl_kernel kernel = clCreateKernel(program , "rev_ascii", &ret) ;
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj) ;
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&c_mem_obj) ;

	size_t global_item_size = N;
	size_t local_item_size = 2 ;

	cl_event event ;
	ret = clEnqueueNDRangeKernel(cmd_q, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, &event) ;
	ret = clFinish(cmd_q) ;

	cl_ulong time_start, time_end ;
	double total_time ;

	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL) ;
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL) ;

	total_time = (double)(time_end - time_start) ;
	ret = clEnqueueReadBuffer(cmd_q, c_mem_obj, CL_TRUE, 0, N*sizeof(char), C, 0, NULL, NULL) ;


	printf(" %s  \n",C) ;

	ret = clFlush(cmd_q) ;
	ret = clReleaseKernel(kernel) ;
	ret = clReleaseProgram(program) ;
	ret = clReleaseMemObject(a_mem_obj) ;
	ret = clReleaseMemObject(c_mem_obj) ;
	ret = clReleaseCommandQueue(cmd_q) ;
	ret = clReleaseContext(context) ;
	free(A);
	free(C) ;
	end = clock() ;
	printf("\n The time for kernel in ms - %0.3f ", total_time/1000000) ;
	printf("\n The time for Program in ms - %0.3f ", (double)(end - start)/1000000) ;
	getchar() ;
	return 0 ;


}
