#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>
#define MAX_SOURCE_SIZE (0x100000)

int main(void){
	int inp[100] ;
	printf("Enter the array length -> ");
	int len ;
	scanf("%d",&len) ;
	printf( "\nEnter the array -> ") ;
	for ( int i = 0 ; i < len ; i++ ) {
		scanf("%d",&inp[i]) ;
	}
	FILE* fp1 , *fp2 ;
	char* source_str1 , *source_str2;
	size_t source_size1 , source_size2;
	fp1=fopen("even_odd.cl","r");
	if(!fp1)
	{
		printf("no\n");

	}
	source_str1=(char*)malloc(MAX_SOURCE_SIZE);
	source_size1=fread(source_str1,1,MAX_SOURCE_SIZE,fp1);
	fclose(fp1);

	fp2=fopen("odd_even.cl","r");
	if(!fp2)
	{
		printf("no\n");

	}
	source_str2=(char*)malloc(MAX_SOURCE_SIZE);
	source_size2=fread(source_str2,1,MAX_SOURCE_SIZE,fp2);
	fclose(fp2);


	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret=clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,ret);
	cl_command_queue command_queue=clCreateCommandQueue(context,device_id,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, len*sizeof(int), NULL, &ret);

	cl_program program1 = clCreateProgramWithSource(context, 1, (const char**)&source_str1 , (const size_t*)&source_size1, &ret);
	cl_program program2 = clCreateProgramWithSource(context, 1, (const char**)&source_str2 , (const size_t*)&source_size2, &ret);

	ret = clBuildProgram(program1, 1, &device_id, NULL, NULL, NULL);
	ret = clBuildProgram(program2, 1, &device_id, NULL, NULL, NULL);

	cl_kernel kernel1 = clCreateKernel(program1, "EvenOdd", &ret);
	cl_kernel kernel2 = clCreateKernel(program2 , "OddEven" , &ret);

	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel2, 0, sizeof(cl_mem), (void*)&a_mem_obj);

	size_t global_item_size = len;
	size_t local_item_size = 1;


	for (int i = 0 ; i < len/2 ;i++) {
		ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(int), inp, 0, NULL, NULL);
		ret = clEnqueueNDRangeKernel(command_queue, kernel1, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(int), inp, 0, NULL, NULL);
		for (int j = 0 ; j < len ;j++)
			printf(" %d ",inp[j] ) ;
		printf("\n");
		ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(int), inp, 0, NULL, NULL);
		ret = clEnqueueNDRangeKernel(command_queue, kernel2, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
		ret = clEnqueueReadBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(int), inp, 0, NULL, NULL);
		for (int j = 0 ; j < len ;j++)
			printf(" %d ",inp[j] ) ;
		printf("\n");
	}

	printf( " After sorting, array -> ") ;
	for (int j = 0 ; j < len ;j++)
		printf(" %d ",inp[j] ) ;
	ret = clFinish(command_queue);
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel1);
	ret = clReleaseKernel(kernel2);
	ret = clReleaseProgram(program1);
	ret = clReleaseProgram(program2);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	getchar();
	return 0;
}
