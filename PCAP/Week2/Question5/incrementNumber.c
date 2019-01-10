#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
	int rank, size, num ;
	MPI_Status status;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	if(rank == 0) {
		printf("Enter number ") ;
		scanf("%d",&num) ;
		MPI_Send(&num,1,MPI_INT,1,0,MPI_COMM_WORLD) ;
		MPI_Recv(&num,1,MPI_INT,size-1,size-1,MPI_COMM_WORLD,&status) ;
		num++ ;
	}
	else {
		MPI_Recv(&num,1,MPI_INT,(rank-1)%size,(rank-1)%size,MPI_COMM_WORLD,&status) ;
		num++ ;
		MPI_Send(&num,1,MPI_INT,(rank+1)%size,rank, MPI_COMM_WORLD ) ;
	}
	printf(" \n%d -> value %d ", rank, num);
	MPI_Finalize() ;
	return 0 ;
}
