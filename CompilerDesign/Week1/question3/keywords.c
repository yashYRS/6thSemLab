#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main() {

	FILE *input  ; 			// Handling file opening 
	char word[20] ;
	char keywords[][20] = {"define", "include", "else", "if", "int", "char", "while", "exit"} ; 
	char keywordsCAPS[][20] = {"DEFINE", "INCLUDE", "ELSE", "IF", "INT", "CHAR", "WHILE", "EXIT"} ; 
	char ch ; 
	int index, flag = 0 , line = 1 , column = 1;   
	input = fopen("input.c", "r") ; 
	if ( input == NULL ) {
		printf("\n Can't open file ");
		exit(0) ; 
	} 
	do {
		ch = getc(input) ;
		flag = 0 ; 
		index = 0 ; 
		while( isalpha(ch)) {
			column++ ; 
			word[index++] = ch ; 							// extract the word
			ch = getc(input) ;
			flag = 1 ;  
		}
		if (flag){
			word[index] = '\0' ;  
			for(int i = 0 ; i < 8 ; i++) {
				if (strcmp(keywords[i], word) == 0 ) {
					printf("\n At %d line number and %d column no ", line, column ) ; 
					puts(keywordsCAPS[i]) ; 
				}
			}			
		}

		if ( ch == '\n') {
			line++ ; 
			column = 1 ; 
		}
		else 
			column++ ;
	}while(ch != EOF ) ; 
	
	fclose(input) ; 					// closing the files 
	return 0 ; 
}