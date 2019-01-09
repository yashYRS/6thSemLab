#include<stdio.h>
#include<stdlib.h>


int main() {
	FILE *input , *output ;
	char ch, next ; 
	int flag ; 
	input = fopen("input.c", "r") ; 
	if ( input == NULL ) {
		printf("\n Can't open file ");
		exit(0) ; 
	}
	output = fopen("output.c","w") ; 
	ch = getc(input) ; 
	while(ch != EOF ) {
		ch = getc(input) ; 
		flag = 0 ; 
		while ( ch == '\t' || ch == ' ')  {
			ch = getc(input) ; 
			flag = 1; 
		}
		if (flag)
			putc(' ',output) ; 
		putc(ch,output) ; 
	}
	fclose(input); 
	fclose(output) ; 
	return 0 ; 

}