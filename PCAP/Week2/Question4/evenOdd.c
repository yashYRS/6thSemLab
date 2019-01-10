#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
	int rank, size, num , num1;
	MPI_Status status;
	int buffer[100] ;
	int bufSize = 100 ;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Buffer_attach(buffer,bufSize) ;
	if(rank == 0) {
		int numbers[size] ;
		printf(" Enter array ") ;
		for(int i = 1 ; i < size ; i++ )
			scanf("%d",&numbers[i]) ;
		for(int i = 1 ; i < size ; i++)
			MPI_Bsend(&numbers[i],1,MPI_INT,i,i, MPI_COMM_WORLD ) ;
	}
	else { //even
		MPI_Recv(&num,1,MPI_INT,0,rank,MPI_COMM_WORLD,&status) ;
		num1 = 1 ;
		if (rank%2 != 0 ) {
			num1 = num ;
		}
		fprintf(stdout,"\n %d -> %d output of process %d\n",num,num*num*num1,rank) ;
	}
	MPI_Buffer_detach(&buffer,&bufSize) ;
	MPI_Finalize() ;
	return 0 ;
}
