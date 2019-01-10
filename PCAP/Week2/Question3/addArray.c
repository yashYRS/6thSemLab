#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	int rank, size, sum1 = 0 , N;
	int numbers[100] ;
	double t1 ;
	MPI_Init(&argc,&argv) ;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	if (size != 2) {
		printf(" Run with -n 2") ;
		exit(0);
	}
	if(rank == 0) {
		printf(" Enter the size of the array ") ;
		scanf("%d",&N) ;
		printf(" Enter array : ") ;
		for(int i = 0 ; i < N ; i++ )
			scanf("%d",&numbers[i]) ;
		MPI_Send(&N,1,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Send(numbers,N,MPI_INT, 1,1,MPI_COMM_WORLD) ;
		t1 = MPI_Wtime() ;
		int sum = 0 ;
		for(int i = 0 ; i < N/2 ; i++)
			sum = sum + numbers[i] ;
		printf("\n %d ends at %f \n", rank,MPI_Wtime()-t1 ) ;
		MPI_Recv(&sum1,1,MPI_INT,1,2,MPI_COMM_WORLD,&status) ;
		sum = sum + 1;
		printf("\n The sum - %d \n",sum + sum1) ;
	}
	else {
		MPI_Recv(&N,1,MPI_INT,0,0,MPI_COMM_WORLD,&status) ;
		MPI_Recv(numbers,N,MPI_INT,0,1,MPI_COMM_WORLD,&status) ;
		sum1 = 0 ;
		t1 = MPI_Wtime() ;
		for(int i = N/2 ; i < N; i++)
			sum1 = sum1 + numbers[i];
		printf("\n %d ends at %f \n", rank,MPI_Wtime()-t1 ) ;
		MPI_Send(&sum1,1,MPI_INT,0,2,MPI_COMM_WORLD) ;

	}
	MPI_Finalize() ;
	return 0 ;
}
