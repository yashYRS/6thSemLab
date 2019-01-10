#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
	int rank, size, num ;
	MPI_Status status;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	if(rank == 0) {
		int numbers[size] ;
		for(int i = 1 ; i < size ; i++ ) {
			numbers[i] = i*10 + 2 ;
			MPI_Send(&numbers[i],1,MPI_INT,i,i, MPI_COMM_WORLD ) ;
		}
	}
	else {
		MPI_Recv(&num,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status) ;
		fprintf(stdout,"I have received %d in process %d\n",num,rank) ;
		fflush(stdout) ;
	}
	MPI_Finalize() ;
	return 0 ;
}
