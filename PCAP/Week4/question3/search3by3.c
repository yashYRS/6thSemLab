#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
	int rank , size , mat[3][3] , search[3] , ele, found = 0, final_found;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank );
	MPI_Comm_size(MPI_COMM_WORLD, &size );
	if (rank == 0) {
		for(int i = 0 ; i < 3 ; i++ ) {
			if(size != 3 ){
				printf(" Enter n = 3 ");
				exit(0);
			}
			printf(" Enter row - ");
			for(int j = 0 ; j < 3 ; j++ )
				scanf("%d",&mat[i][j]) ;
		}
		printf(" Enter element to be searched - ") ;
		scanf("%d",&ele) ;
	}
	MPI_Bcast(&ele, 1 , MPI_INT , 0 , MPI_COMM_WORLD) ;
	MPI_Scatter(mat, 3, MPI_INT ,search, 3, MPI_INT, 0 , MPI_COMM_WORLD);
	for(int i = 0 ; i < 3 ; i++) {
		if (search[i] == ele)
			found++ ;
	}
	MPI_Reduce(&found, &final_found, 1, MPI_INT, MPI_SUM, 0 , MPI_COMM_WORLD) ;
	if(rank == 0)
		printf(" The number of occurrences :- %d ",final_found ) ;
	MPI_Finalize() ;
	return 0 ;
}
