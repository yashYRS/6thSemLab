#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]) {
	int rank , size , mat[4][4] , summing[4] ,sum[4];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank );
	MPI_Comm_size(MPI_COMM_WORLD, &size );
	if (rank == 0) {
		for(int i = 0 ; i < 4 ; i++ ) {
			if(size != 4 ){
				printf(" Enter n = 4 ");
				exit(0);
			}
			printf(" Enter row - ");
			for(int j = 0 ; j < 4 ; j++ )
				scanf("%d",&mat[i][j]) ;
		}
	}
	MPI_Scatter(mat, 4, MPI_INT ,summing, 4, MPI_INT, 0 , MPI_COMM_WORLD);
	for(int i = 0 ; i < 4 ; i++ ){
		MPI_Scan(&summing[i], &sum[i], 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD) ;
	}
	MPI_Gather(&sum[0],4,MPI_INT, &mat,4, MPI_INT, 0, MPI_COMM_WORLD) ;
	if (rank == 0) {
		printf("\n The final Matrix :-\n ") ;
		for(int i = 0 ; i < 4 ; i++){
			for(int j = 0 ; j < 4 ; j++)
				printf(" %d ",mat[i][j]) ;
			printf("\n") ;
		}
	}
	MPI_Finalize() ;
	return 0 ;
}
