#include<mpi.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
	for(int i = 0 ; i < 30 ; i ++ )
		printf("%d ", i);
	printf("\n") ;
	int rank, size ;
	int a = 10 , b = 4;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank) ;
	MPI_Comm_size(MPI_COMM_WORLD,&size) ;
	if (rank == 0)
		printf("\n Add - %d",a + b) ;
	else if (rank == 1)
		printf("\n Sub - %d",a - b );
	else if (rank == 2)
		printf("\n Mul - %d",a*b );
	else
		printf("\n Div - %f",(float)a/(float)b) ;
	MPI_Finalize();
	return 0 ;
}
