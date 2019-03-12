#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[]) {
	int rank, size , len;
	char input[2][100] , temp[2][20] , newTemp[40], final[100];
	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	if (rank == 0) {
		for (int i = 0 ; i < 2 ; i++ ) {
			fprintf(stdout, "\n Enter string : ") ;
			fflush(stdout) ;
			scanf("%s",input[i]);
		}
		len = strlen(input[0]) ;
	}
	MPI_Bcast(&len, 1, MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(input[0], len/size, MPI_CHAR, temp[0], len/size, MPI_CHAR, 0 , MPI_COMM_WORLD) ;
	MPI_Scatter(input[1], len/size, MPI_CHAR, temp[1], len/size, MPI_CHAR, 0 , MPI_COMM_WORLD) ;
	fflush(stdout);
	strcpy(newTemp,"") ;
	for( int i = 0 ; i < len/size ; i++) {
		newTemp[i*2] = temp[0][i] ;
		newTemp[i*2 + 1] = temp[1][i] ;
	}
	newTemp[2*len/size] = '\0' ;
	MPI_Gather(&newTemp, strlen(newTemp), MPI_CHAR, final, strlen(newTemp), MPI_CHAR, 0 , MPI_COMM_WORLD) ;
	if (rank == 0 ) {
		final[2*len] = '\0' ;
		fprintf(stdout, "%s", final);
		fflush(stdout) ;
	}
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
