#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>
#define MAX_SOURCE_SIZE (0x100000)

int main(void){
	int i, count=0;
	char str[100] , word[50];
	int startInd[100] , endInd[100] , wordcount[100] ;

	printf("Enter the string \n");
	fgets(str, 100 , stdin) ;
	int len = strlen(str) ;

	printf( " Enter the word to be found ");
	fgets(word, 50 , stdin) ;

	FILE* fp;
	char* source_str;
	size_t source_size;
	fp=fopen("wordcount.cl","r");
	if(!fp)
	{
		printf("no\n");

	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size=fread(source_str,1,MAX_SOURCE_SIZE,fp);

	int num = 0 ;
	startInd[0] = 0 ;
	for (int i = 1 ; i < len ; i++ ) {
		if (str[i] == ' ') {
			startInd[num+1] = i+1 ;
			endInd[num] = i-1 ;
			wordcount[num] = 0 ;
			num++ ;
		}
	}
	endInd[num] = len-1;
	fclose(fp);

	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret=clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret = clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_GPU,1,&device_id,&ret_num_devices);
	cl_context context = clCreateContext(NULL,1,&device_id,NULL,NULL,ret);
	cl_command_queue command_queue=clCreateCommandQueue(context,device_id,NULL,&ret);

	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, len*sizeof(char), NULL, &ret);
	cl_mem word_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, strlen(word)*sizeof(char), NULL, &ret);
	cl_mem start_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, num*sizeof(int), NULL, &ret);
	cl_mem end_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, num*sizeof(int), NULL, &ret);
	cl_mem count_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, num*sizeof(int), NULL, &ret);

	ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, len*sizeof(char), str, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, word_mem_obj, CL_TRUE, 0, strlen(word)*sizeof(char), word, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, start_mem_obj, CL_TRUE, 0, num*sizeof(int), startInd, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, end_mem_obj, CL_TRUE, 0, num*sizeof(int), endInd, 0, NULL, NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t*)&source_size, &ret);
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "WordFind", &ret);
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&start_mem_obj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&end_mem_obj);
	ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&word_mem_obj);
	ret = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&count_mem_obj);


	size_t global_item_size = num;
	size_t local_item_size = 1;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(command_queue, count_mem_obj, CL_TRUE, 0, num*sizeof(int), wordcount, 0, NULL, NULL);
	ret = clFinish(command_queue);
	int count_words = 0 ;
	for ( int i = 0 ; i < num ; i++ ) {
		if (wordcount[i] == 1 )
			count_words++ ;
	}
	printf( "Number of matches - %d " , count_words) ;
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(a_mem_obj);
	ret = clReleaseMemObject(word_mem_obj);
	ret = clReleaseMemObject(start_mem_obj);
	ret = clReleaseMemObject(end_mem_obj);
	ret = clReleaseMemObject(count_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	getchar();
	return 0;
}
