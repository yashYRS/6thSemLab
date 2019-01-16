#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


struct Token {
	int trow ; 
	int tcol ; 
	char *lex ; 
	char *type ; 
} ; 

typedef struct Token *tokenptr ; 

int row = 1 , col = 0 , initrow , initcol , flag = 0 , ind ; 
char curr, curr2 ;
char keywords[][20] = {"for","do","printf","return","else", "if", "int", "char", "while", "exit", "switch", "void"} ; 

void rowCol(char c) {
	if (c == '\n')  {
		row = row + 1 ; 
		col = 0 ; 		return ; 
	} 
	if (c != EOF )
		col = col + 1; 
}

void printToken(int r , int c , char *lex, char *type) {
	printf("\nAt row - %d , col - %d : lexeme ->  %s , type -> %s",r,c, lex , type );
}


int getNextToken(FILE *input) {
	char temp[20] ;  
	while (curr != EOF ) { 
		if (curr == '/') {  
			curr2 = getc(input) ; 
			rowCol(curr2) ; 
			if (curr2 == '/') {				// single line comment 
				do {
					curr2 = getc(input) ;
					rowCol(curr2) ;  
				}while(curr2 != '\n') ; 
			} 	
			else if ( curr2 == '*') {		// multi line comment 
				while(1) {
					curr2 = getc(input) ;
					rowCol(curr2) ; 
					if (curr2 == '*') {
						curr2 = getc(input) ; 
						rowCol(curr2) ; 
						if ( curr2 == '/')
							break ; // exit this loop 
					}
				}
			} 
			else {
				strcpy(temp, "") ; 
				temp[0] = curr ; 
				temp[1] = '\0' ; 				
				printToken(row, col, temp, "Arithmetic") ; 
				curr = getc(input) ; 
				rowCol(curr) ; 
				return 1 ;
			} 				// division 
		}

		if ( curr == '#') {												// Preprocessor 
			ind = 0 ; 
			curr2 = getc(input) ; 
			rowCol(curr2) ; 
			initcol = col ; 
			initrow = row ; 
			while( isalpha(curr2)) {
				temp[ind++] = curr2 ; 						
				curr2 = getc(input) ;
				rowCol(curr2) ; 
			}
			temp[ind] = '\0' ;  
			if ( strcmp(temp,"include") == 0  || strcmp(temp, "define") == 0 ) {
				printToken(initrow, initcol ,temp , "Preprocessor") ; 
				while(curr2!= '\n') {
					curr2 = getc(input) ; 			
					rowCol(curr2) ; 
				}
				curr = getc(input) ; 
				rowCol(curr) ; 
				return 1 ; 
			}
		}
		if (curr == '+' || curr == '*' || curr == '-') {		// Arithmetic
			curr2 = getc(input) ; 
			if (curr2 != curr) {
				strcpy(temp, "") ; 
				temp[0] = curr ; 
				temp[1] = '\0' ; 
				printToken(row, col, temp, "Arithmetic") ;
			}
			curr = curr2 ; 
			rowCol(curr) ; 
			return 1 ; 
		}

		if (curr == '"') {										// string literal  
			strcpy(temp, "") ; 
			temp[0] = curr ; 
			temp[1] = '\0' ; 
			printToken(row, col, temp, "String") ;	
			do {	
				curr2 = getc(input) ; 
				rowCol(curr2) ; 
			}while(curr2 != '"') ; 		
		}	

		if (curr == '>' || curr == '<' || curr == '!' || curr == '=' ) { 		// Relational 
			curr2 = getc(input) ; 
			temp[0] = curr ;
			temp[1] = curr2 ; 
			temp[2] = '\0' ; 
 			if (curr2 == '=')
				printToken(row,col, temp , "Relational") ; 
			else if (curr == '=') 
				printToken(row, col, temp, "Assignment") ; 
			else 
				printToken(row,col, temp , "Relational") ; 
			rowCol(curr2) ; 
			curr = curr2 ; 
			return 1; 
		}

		if (curr == '&' || curr == '|' || curr == '^'){ 	// Logical Operators 
			curr2 = getc(input) ; 
			temp[0] = curr ;
			temp[1] = curr2 ; 
			if (curr2 != curr)  {
				temp[1] = '\0' ; 				
				printToken(row, col , temp, "Logical") ; 
				curr = curr2 ; 
				rowCol(curr) ; 
				return 1 ; 
			}
			else {
				temp[2] = '\0' ; 
				printToken(row, col, temp, "Logical") ; 
				return 1; 
			}
		} 	

		if ( isdigit(curr) ) {						// Numerical Constants 
			strcpy(temp,"") ; 
			ind = 0 ;
			curr2 = curr ;  
			do {
				temp[ind++] = curr2 ;  
				curr2 = getc(input) ; 
				rowCol(curr) ;  
			}while(isdigit(curr2)) ; 
			temp[ind] = '\0' ; 
 			printToken(row, col-ind ,temp, "Numerical") ; 
			curr = curr2 ; 
			return 1;  
		}

		if ( curr == '(' || curr == ')' || curr == '}' || curr == '{' || curr == ';') {
			strcpy(temp , "") ; 
			temp[0] = curr ; 
			temp[1] = '\0' ; 
			printToken(row, col , temp, "Special") ; 
		} 	// Special 

		curr2 = curr ; 
		ind = 0 ;  flag = 0 ; 
		initrow = row ; initcol = col ; 	
		if (isalpha(curr2) || curr2 == '_') {									// Keywords and identifiers
			while( isalpha(curr2) || isdigit(curr2) || curr2 == '_') {
				temp[ind++] = curr2 ; 
				curr2 = getc(input) ; 
				rowCol(curr2) ; 
			}
			temp[ind] = '\0' ; 
			for (int i = 0 ; i < 12 ; i++) {
				if (strcmp(keywords[i], temp) == 0 ) {
					printToken(initrow, initcol, temp , "Keyword") ; 
					flag = 1 ; 
				}
			}
			if (flag != 1) 
				printToken(initrow, initcol , temp , "identifier") ; 
		}
		else {
			 curr = getc(input) ; 
			 rowCol(curr) ; 
			 continue  ; 
		}
		curr = curr2 ; 
	}	
	return 0 ; 
}
int main() {

	FILE *input = fopen("input.c","r") ; 
	if (!input) {
		printf("Can't open file ") ; 
		exit(0) ; 
	}
	curr = getc(input) ; 
 	rowCol(curr) ; 
 	while(1){
 		if (getNextToken(input) == 0) 
 			break; 
 	} 
	fclose(input) ; 
	return 0 ; 
}