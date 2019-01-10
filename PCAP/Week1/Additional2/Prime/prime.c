#include<mpi.h>
#include<stdio.h>
void checkPrime(int a) {
	int flag = 0 ;
	for(int i = 2 ; i <= a/2 ; i++)
		if (a%i == 0)
			flag = 1 ;
	if (flag == 0)
		printf("%d ", a) ;
}

int main(int argc,char *argv[]) {
	int r ;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&r) ;
	if ( r == 0 ) {
		//parent
		for (int i = 2 ; i < 400 ; i++) {
			checkPrime(i);
		}
	}
	else { //other
		for(int i = 400 ; i < 1000; i++) {
			checkPrime(i) ;
		}
	}
	MPI_Finalize();
	return 0 ;
}
