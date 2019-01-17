#include "mpi.h"
#include<stdio.h>

int main(int argc , char *argv[]) {
	int rank, size ,A[100], Recv[10],i,j, m ;
	float ave = 0, totAve = 0 ;
	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	if (rank == 0) {
		fprintf(stdout, "Enter m ") ;
		fflush(stdout) ;
		scanf("%d",&m) ;
		for(i = 0 ; i< size ;i++) {
			fprintf(stdout,"\n Enter %d values : ", m) ;
			fflush(stdout) ;
			for (j = 0 ; j < m ;j++)
				scanf("%d", &A[i*m + j]) ;
		}

	}
	MPI_Bcast(&m, 1, MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A, m, MPI_INT, &Recv, m, MPI_INT, 0 , MPI_COMM_WORLD) ;
	fflush(stdout);
	for (i = 0 ; i < m ; i++) {
		ave = ave + Recv[i];
	}

	ave = ave/m ;
	MPI_Reduce(&ave, &totAve , 1, MPI_FLOAT , MPI_SUM, 0 , MPI_COMM_WORLD) ;
	if (rank == 0 ) {
		totAve = totAve/size ;
		fprintf(stdout, " The result - %f ", totAve ) ;
		fflush(stdout) ;
	}
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
