#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {
	int rank, size ,A[10], c , i , product = 1,sum ;
	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	if (rank == 0) {
		fprintf(stdout," Enter %d values : \n ", size) ;
		fflush(stdout) ;
		for(i = 0 ; i< size ;i++)
			scanf("%d", &A[i]) ;
	}
	MPI_Scatter(A, 1, MPI_INT, &c, 1, MPI_INT, 0 , MPI_COMM_WORLD) ;
	for (i = 2 ; i <= c ; i++)
		product = product*i ;
	MPI_Reduce(&product, &sum , 1, MPI_INT , MPI_SUM , 0 , MPI_COMM_WORLD) ;
	if (rank == 0 ) {
		fprintf(stdout, " The result - %d ", sum ) ;
		fflush(stdout) ;
	}
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
