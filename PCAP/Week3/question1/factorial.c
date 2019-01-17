#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {
	int rank, size ,A[10], c , i , product = 1;
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
	fprintf(stdout, " I have received %d in process %d \n", product, rank) ;
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
