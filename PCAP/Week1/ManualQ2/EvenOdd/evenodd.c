#include<mpi.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	int rank, size ;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	for (int i = 0 ; i < size ; i++) {
		if (rank == i) {
			if (i%2 == 0) { //even
				printf("\n Hello, from Rank - %d ",rank) ;
			}
			else {
				printf("\n World, from Rank - %d ", rank) ;
			}
		}
	}
	MPI_Finalize() ;
	return 0 ;
}
