#include<stdio.h>
#include "mpi.h"

int main(int argc, char *argv[]){
	int n, rank , size , i ;
	float finalPi , myPi , h, x, sum ;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	if (rank == 0 ) {
			printf( " Enter the number of strips :- ") ;
			scanf("%d",&n) ;
	}
	MPI_Bcast(&n,1, MPI_INT , 0 , MPI_COMM_WORLD) ;
	h = 1.0/(double) n ;
	sum = 0.0 ;
	for (i = rank+1 ; i <= n ; i+= size) {
		x = h*((double)i - 0.5) ;
		sum+= 4.0/(1+x*x) ;
	}
	myPi = sum*h ;
	MPI_Reduce(&myPi ,&finalPi, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD) ;
	if (rank == 0)
		printf("%f", finalPi) ;


	MPI_Finalize() ;
	return 0 ;
}
