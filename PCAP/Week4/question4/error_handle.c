#include<stdio.h>
#include "mpi.h"


void handle(int err) {
	int err_class, len ;
	char err_str[200] ;
	if (err!= MPI_SUCCESS) {
		MPI_Error_class(err, &err_class) ;
		MPI_Error_string(err_class, err_str, &len) ;
		printf("\n Error class : %d , Message - %s ", err_class, err_str) ;
	}
}
int main(int argc, char *argv[]) {

	int rank ,size,err_code;
	MPI_Init(&argc, &argv) ;
	MPI_Errhandler_set(MPI_COMM_WORLD , MPI_ERRORS_RETURN) ;
	err_code = MPI_Comm_rank(MPI_COMM_WORLD, &rank) ;
	err_code = MPI_Comm_size(3, &size); // Intentional Error
	handle(err_code) ;
	err_code = MPI_Finalize() ;
	handle(err_code) ;
	return 0 ;
}
