#include<stdio.h>
#include<string.h>
#include "lex.yy.c"

struct token *t_ptr;

int E_func() ; 
int E1_func() ; 
int T_func() ; 
int T1_func() ; 
int F_func() ; 

struct token* getNextToken() {
	struct token *temp ; 
	temp = yylex() ; 
	if ( !temp ) 
		temp = NULL ; 
	return temp ; 
}

int E_func() {
	printf( " \n In E_func() " ) ; 	
	if ( T_func() == 1) 
		return E1_func() ; 
	return 0 ; 
}

int E1_func() {
	printf(" \n In E1_func() " ) ; 
	if ( t_ptr &&  strcmp(t_ptr->lexeme, "+")==0 ) 	{
		t_ptr = getNextToken() ; 
		if ( T_func() == 1 ) 
			return E1_func() ; 
		return 0 ; 
	}
	return 1 ; 

}

int T_func() {
	printf( " \n In T_func() " ) ; 
	if ( F_func() == 1) 
		return T1_func() ; 	
	return 0 ; 
	
}

int T1_func() {
	printf( " \n In T1_func() " ) ; 
	if ( t_ptr && strcmp(t_ptr->lexeme , "*") == 0 ) {
		printf( " %s " , t_ptr->lexeme) ; 
		t_ptr = getNextToken() ; 	
		if ( F_func() == 1) 
			return T1_func() ; 	 
		else 
			return 0 ; 
	}
	return 1 ; 
}

int F_func() {
	printf(" \n In F_func() ") ; 
	if ( t_ptr && strcmp(t_ptr->lexeme, "id") == 0 ) {
		t_ptr = getNextToken() ; 		
		return 1 ;  
	}
	else if ( t_ptr && strcmp( t_ptr->lexeme , "(") == 0 ) {
		t_ptr = getNextToken() ; 
		if ( E_func() == 1 ) { 
			if ( t_ptr && strcmp( t_ptr->lexeme , ")" ) == 0 )  {
				t_ptr = getNextToken() ; 
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
	


int main() {
	yyin = fopen("test.c", "r");

	// Call on the start function  
	t_ptr = getNextToken();
	int retVal ; 	
	retVal = E_func();
	
	if ( retVal == 1 ) 
		printf( " Accept ") ; 
	else 
		printf("Reject\n");

}

