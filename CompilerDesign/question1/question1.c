#include<stdio.h>
#include<string.h>
#include "lex.yy.c"

struct token *t_ptr;

int S_func() ; 
int T_func() ; 
int T1_func() ; 

struct token* getNextToken() {
	struct token *temp ; 
	temp = yylex() ; 
	if ( !temp ) 
		temp = NULL ; 
	return temp ; 
}

int S_func() {
	int retVal ; 
	printf( " \n In s_func() " ) ; 	
	if ( t_ptr && ( strcmp(t_ptr->lexeme,"a") == 0 || strcmp(t_ptr->lexeme, ">") == 0 ) ) {
		printf( " %s " , t_ptr->lexeme) ;  			
		t_ptr = getNextToken() ; // go to the next symbol 
		return 1 ; 
	}
	
	else if ( t_ptr && strcmp(t_ptr->lexeme,"(")==0 ) {
		printf( " %s " , t_ptr->lexeme) ; 
		t_ptr = getNextToken() ; 
		retVal = T_func() ; 
		if ( retVal == 0 ) 
			return 0 ; 

		if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 )  {
			printf( " %s " , t_ptr->lexeme) ; 		
			return 1 ;
		}
	}
}

int T_func() {
	printf( " \n In t_func() " ) ; 
	if ( S_func() == 1) 
		return T1_func() ; 	
	return 0 ; 
	
}

int T1_func() {
	printf( " \n In t1_func() " ) ; 
	if ( t_ptr && strcmp(t_ptr->lexeme , ",") == 0 ) {
		printf( " %s " , t_ptr->lexeme) ; 
		t_ptr = getNextToken() ; 	
		if ( S_func() == 1) 
			return T1_func() ; 	 
		else 
			return 0 ; 
	}
	return 1 ; 
}


int main() {

	yyin = fopen("test.c", "r");

	// Call on the start function  
	t_ptr = getNextToken();
	int retVal ; 	
	retVal = S_func();
	
	if ( retVal == 1 ) 
		printf( " Accept ") ; 
	else 
		printf("Reject\n");

}

