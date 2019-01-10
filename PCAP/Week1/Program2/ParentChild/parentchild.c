#include<mpi.h>
#include<stdio.h>
int main(int argc, char *argv[]) {

	MPI_Init(&argc,&argv);
	int a, rank ;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank) ;
	if (rank == 0) {
		a = 5 ;
		printf("\n value of a - %d ",a) ;
	}
	else {
		a = 3 ;
		printf("\n Value of a - %d ",a) ;
	}
	MPI_Finalize() ;
	return 0 ;
}
