#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[]) {
	int rank, size , len , ascii[20], final_ascii[100] ;
	char input[100] , temp[20], final[100];
	MPI_Init(&argc, &argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	if (rank == 0) {
		fprintf(stdout, "\n Enter string (len should be divisible by N) : ") ;
		fflush(stdout) ;
		scanf("%s",input);
		len = strlen(input) ;
	}
	MPI_Bcast(&len, 1, MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(input, len/size, MPI_CHAR, &temp, len/size, MPI_CHAR, 0 , MPI_COMM_WORLD) ;
	fflush(stdout);
	temp[len] = '\0' ;
	for (int i = 0 ; i < len/size ; i++) {
		if (temp[i] < 123 && temp[i] > 96 )
			temp[i] = temp[i] - 32 ;
		else if (temp[i] < 91 && temp[i] > 64 )
			temp[i] = temp[i] + 32 ;
		ascii[i] = (int)temp[i] ;
	}
	MPI_Gather(&temp, len/size, MPI_CHAR,final, len/size, MPI_CHAR, 0 , MPI_COMM_WORLD) ;
	MPI_Gather(&ascii, len/size, MPI_INT,final_ascii, len/size, MPI_INT, 0 , MPI_COMM_WORLD) ;
	if (rank == 0 ) {
		for( int i = 0 ; i < len ; i++ ) {
			fprintf(stdout, "\n %d - ascii, %c - char ", final_ascii[i], final[i]);
			fflush(stdout) ;
		}
	}
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
