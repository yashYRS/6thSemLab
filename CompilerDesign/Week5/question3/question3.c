#include<stdio.h>
#include<string.h> 
#include "lex.yy.c"

struct token *t_ptr ; 
int curr_char = 0 ; 
struct token *get_next() { 
	struct token *temp = yylex() ; 
	if (!temp)
		return NULL ; 
	return temp ; 
}

int B_func() {
	if (t_ptr && t_ptr->lexeme[curr_char] == 'd' )  {
		curr_char++ ; 
		return 1 ; 
	}
	return 0 ; 

}


int Ad_func() {
	int retval ; 
	if (t_ptr && t_ptr->lexeme[curr_char] == 'b')  {
		curr_char++ ; 
		retval = Ad_func() ; 
		if ( retval == 1 ) {
			curr_char++ ; 
			return 1 ; 
		}
		else 
			return 0 ; 
	}
	return 1 ; 
}

int A_func() {
	int retval ; 
	if (t_ptr && t_ptr->lexeme[curr_char] == 'b')  {
		curr_char++ ; 
		return Ad_func() ; 
	}
	return 0 ; 	
}


int S_func()  {

	int retval ; 
	if ( t_ptr && t_ptr->lexeme[curr_char] == 'a' ) { // all the other options possible 
		curr_char++ ; 
		retval = A_func() ; 
		printf(" a done ") ; 
		if ( retval == 1 ) {
			printf(" A done ") ; 
			if ( t_ptr && t_ptr->lexeme[curr_char] == 'c' ) { 
				curr_char++ ; 
				printf(" c done ") ; 
				retval = B_func() ; 
				if ( retval == 1 ) {
					printf(" B done ") ; 
					if ( t_ptr && t_ptr->lexeme[curr_char] == 'e' ) { 
						printf(" e done ") ; 
						curr_char++ ; 
						return 1 ; 
					}
					else 
						return 0 ; 
				}
				else 
					return 0 ; 
			}
			else 
				return 0 ; 
		}
		else 
			return 0 ; 	
	}
	else 
		return 0 ; 

}



int main() {

	yyin = fopen("test.c" , "r") ; 
	t_ptr = get_next() ; 
	printf("%s\n",t_ptr->lexeme );
	int retval = S_func() ; 
	if ( retval == 1 )
		printf(" Accept\n");
	else 
		printf(" Reject \n");

}