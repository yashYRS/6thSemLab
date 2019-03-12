#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


struct Token {
	int trow ; 
	int tcol ; 
	char lex[20] ; 
	char type[20] ; 
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
	printf("\n<%s ,%d ,%d ,%s >",lex,r,c, type );
}


int getNextToken(FILE *input) {
	char temp[20] ;  
	tokenptr newtoken = (tokenptr) malloc(sizeof(struct Token)) ; 
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
						if ( curr == '/')
							break ; // exit this loop 
					}
				}
			} 
			else {
				strcpy(temp, "") ; 
				temp[0] = curr ; 
				temp[1] = '\0' ; 				
				printToken(row, col, temp, "Arithmetic") ; 
				newtoken->trow = row ; 
				newtoken->tcol = col ; 
				strcpy(newtoken->lex,temp) ; 
				strcpy(newtoken->type, "Arithmetic") ; 
				curr = getc(input) ; 
				rowCol(curr) ; 
				return 1 ;
			} 				// division 
		}

		if ( curr == '#') {												// Preprocessor 
			ind = 0 ; 
			curr = getc(input) ; 
			rowCol(curr) ; 
			initcol = col ; 
			initrow = row ; 
			while( isalpha(curr)) {
				temp[ind++] = curr ; 						
				curr = getc(input) ;
				rowCol(curr) ; 
			}
			temp[ind] = '\0' ;  
			if ( strcmp(temp,"include") == 0  || strcmp(temp, "define") == 0 ) {				
				while(curr!= '\n') {
					curr = getc(input) ; 			
					rowCol(curr) ; 
				}
				curr = getc(input) ; 
				rowCol(curr) ; 
				return 1 ; 
			}
		}
		if (curr == '+' || curr == '*' || curr == '-') {		// Arithmetic
			curr = getc(input) ; 
			if (curr != curr) {
				strcpy(temp, "") ; 
				temp[0] = curr ; 
				temp[1] = '\0' ; 
				printToken(row, col, temp, "Arithmetic") ;
				newtoken->trow = row ; 
				newtoken->tcol = col ; 
				strcpy(newtoken->lex,temp) ; 
				strcpy(newtoken->type, "Arithmetic") ; 				
			}
			curr = curr ; 
			rowCol(curr) ; 
			return 1 ; 
		}

		if (curr == '"') {										// string literal  
			strcpy(temp, "") ; 
			temp[0] = curr ; 
			temp[1] = '\0' ; 
			printToken(row, col, temp, "String") ;	
			newtoken->trow = row ; 
			newtoken->tcol = col ; 
			strcpy(newtoken->lex,temp) ; 
			strcpy(newtoken->type, "String") ; 			
			do {	
				curr = getc(input) ; 
				rowCol(curr) ; 
			}while(curr != '"') ; 		
			return 1 ; 
		}	

		if (curr == '>' || curr == '<' || curr == '!' || curr == '=' ) { 		// Relational 
			curr = getc(input) ; 
			temp[0] = curr ;
			temp[1] = curr ; 
			temp[2] = '\0' ; 
			newtoken->trow = row ; 
			newtoken->tcol = col ; 
			strcpy(newtoken->lex,temp) ; 
 			if (curr == '=') {
				printToken(row,col, temp , "Relational") ; 
				strcpy(newtoken->type, "Relational") ; 			
			}
			else if (curr == '=') {
				printToken(row, col, temp, "Assignment") ; 
				strcpy(newtoken->type, "Assignment") ; 			
			}
			else { 
				printToken(row,col, temp , "Relational") ; 
				strcpy(newtoken->type, "Relational") ; 			
			}
			rowCol(curr) ; 
			curr = curr ; 
			return 1; 
		}

		if (curr == '&' || curr == '|' || curr == '^'){ 	// Logical Operators 
			curr = getc(input) ; 
			temp[0] = curr ;
			temp[1] = curr ; 
			if (curr != curr)  {
				temp[1] = '\0' ; 				
				printToken(row, col , temp, "Logical") ; 
				newtoken->trow = row ; 
				newtoken->tcol = col ; 
				strcpy(newtoken->lex,temp) ; 
				strcpy(newtoken->type, "Logical") ; 					
				curr = curr ; 
				rowCol(curr) ; 
				return 1 ; 
			}
			else {
				temp[2] = '\0' ; 
				printToken(row, col, temp, "Logical") ; 
				newtoken->trow = row ; 
				newtoken->tcol = col ; 
				strcpy(newtoken->lex,temp) ; 
				strcpy(newtoken->type, "Logical") ; 	
				return 1; 
			}
		} 	

		if ( isdigit(curr) ) {						// Numerical Constants 
			strcpy(temp,"") ; 
			ind = 0 ;
			curr = curr ;  
			do {
				temp[ind++] = curr ;  
				curr = getc(input) ; 
				rowCol(curr) ;  
			}while(isdigit(curr)) ; 
			temp[ind] = '\0' ; 
 			printToken(row, col-ind ,temp, "Numerical") ; 
			newtoken->trow = row ; 
			newtoken->tcol = col ; 
			strcpy(newtoken->lex,temp) ; 
			strcpy(newtoken->type, "Numerical") ; 	 			
			curr = curr ; 
			return 1;  
		}

		if ( curr == '(' || curr == ')' || curr == '}' || curr == '{' || curr == ';') {
			strcpy(temp , "") ; 
			temp[0] = curr ; 
			temp[1] = '\0' ; 
			printToken(row, col , temp, "Special") ; 
			newtoken->trow = row ; 
			newtoken->tcol = col ; 
			strcpy(newtoken->lex,temp) ; 
			strcpy(newtoken->type, "Special") ; 	
			return 1 ; 			
		} 	// Special 

		curr = curr ; 
		ind = 0 ;  flag = 0 ; 
		initrow = row ; initcol = col ; 	
		if (isalpha(curr) || curr == '_') {									// Keywords and identifiers
			while( isalpha(curr) || isdigit(curr) || curr == '_') {
				temp[ind++] = curr ; 
				curr = getc(input) ; 
				rowCol(curr) ; 
			}
			temp[ind] = '\0' ; 
			for (int i = 0 ; i < 12 ; i++) {
				if (strcmp(keywords[i], temp) == 0 ) {
					printToken(initrow, initcol, temp , "Keyword") ; 
					newtoken->trow = row ; 
					newtoken->tcol = col ; 
					strcpy(newtoken->lex,temp) ; 
					strcpy(newtoken->type, "Keyword") ; 						
					flag = 1 ; 
				}
			}
			if (flag != 1)  {
				printToken(initrow, initcol , temp , "identifier") ; 
				newtoken->trow = row ; 
				newtoken->tcol = col ; 
				strcpy(newtoken->lex,temp) ; 
				strcpy(newtoken->type, "String") ; 	
			}
			return 1 ; 
		}
		else {
			 curr = getc(input) ; 
			 rowCol(curr) ; 
			 continue  ; 
		}
		//curr = curr ; 
	}	
	return 0 ; 
}
int prompt() {
	printf("\n 1. Get Token 2. Exit \n Enter your choice -> " );
	int a ; scanf("%d",&a) ; return a; 
}
int main() {

	FILE *input = fopen("test.c","r") ; 
	if (!input) {
		printf("Can't open file ") ; 
		exit(0) ; 
	}
 
 	while(1){
 		switch(prompt()) {	
 			case 1 :
 					curr = getc(input) ; 
 					rowCol(curr) ; 
 					if (getNextToken(input) == 0)
 						exit(0); 
 					break; 
			case 2 : exit(0); 
		}

 	} 
	fclose(input) ; 
	return 0 ; 
}
