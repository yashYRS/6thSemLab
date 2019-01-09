#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main() {

	FILE *input , *output ; 			// Handling file opening 
	char word[20] ;
	char ch ; 
	int index, flag = 0  ;   
	input = fopen("input.c", "r") ; 
	if ( input == NULL ) {
		printf("\n Can't open file ");
		exit(0) ; 
	}
	output = fopen("output.c","w") ; 
	
	do {
		ch = getc(input) ; 
		flag = 0 ;  
		if ( ch == '#') {
			index = 0 ; 
			ch = getc(input) ; 
			while( isalpha(ch)) {
				word[index++] = ch ; 							// extract the word
				ch = getc(input) ;
			}
			word[index] = '\0' ;  
			puts(word) ; 
			if ( strcmp(word,"include") == 0  || strcmp(word, "define") == 0 ) {
				while(ch!= '\n') 
					ch = getc(input) ; 			// ignore till the end of the line 
				flag = 1 ; 	
			}
		}
		if (!flag) 
			putc(ch,output) ; 
	
	}while(ch != EOF ) ; 
	
	fclose(input) ; 					// closing the files 
	fclose(output) ; 
	return 0 ; 
}