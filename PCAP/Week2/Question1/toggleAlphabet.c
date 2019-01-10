#include "mpi.h"
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
	int rank, size, len ;
	char data[40] ;
	MPI_Init(&argc,&argv) ;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &size) ;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	if (size != 2) {
		printf(" Run with -n 2") ;
		exit(0);
	}
	if(rank == 0) {
		printf(" Enter a string ") ;
		fgets(data,40,stdin) ;
		len = (int)strlen(data) ;
		MPI_Ssend(&len,1,MPI_INT,1,0, MPI_COMM_WORLD ) ;
		MPI_Ssend(data,len+1,MPI_CHAR,1,1,MPI_COMM_WORLD) ;
		MPI_Recv(data,len+1, MPI_CHAR,1,2, MPI_COMM_WORLD,&status) ;
		fputs(data,stdout) ;
	}
	else {
		MPI_Recv(&len,1,MPI_INT,0,0,MPI_COMM_WORLD,&status) ;
		MPI_Recv(data,len + 1, MPI_CHAR,0,1, MPI_COMM_WORLD,&status) ;
		fputs(data,stdout);
		for(int i = 0 ; i < len ; i++) {
			if (data[i] < 123 && data[i] > 96)
				data[i] = data[i] - 32 ;
			else if (data[i] < 91 && data[i] > 64)
				data[i] = data[i] + 32 ;
		}
		MPI_Ssend(data,len,MPI_CHAR,0,2,MPI_COMM_WORLD) ;
	}
	MPI_Finalize() ;
	return 0 ;
}
