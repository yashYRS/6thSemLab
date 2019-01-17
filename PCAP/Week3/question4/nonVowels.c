#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[]) {
	int rank, size , len , num = 0 , nonVowels[20] , total = 0 ;
	char input[100] , temp[20] ;
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
		if (temp[i]!= 'a' && temp[i]!= 'e' && temp[i]!= 'o' && temp[i]!= 'i' && temp[i]!= 'u')
			num++ ;
	}
	MPI_Gather(&num, 1, MPI_INT, nonVowels, 1, MPI_INT, 0 , MPI_COMM_WORLD) ;
	if (rank == 0 ) {
		for( int i = 0 ; i < size ; i++ ) {
			fprintf(stdout, "\n Non Vowels - %d, in process - %d  ", nonVowels[i], i) ;
			total = nonVowels[i] + total ;
			fflush(stdout) ;
		}
		fprintf(stdout, "\n Total - %d   ", total) ;
		fflush(stdout) ;
	}
	fflush(stdout);
	MPI_Finalize() ;
	return 0 ;
}
