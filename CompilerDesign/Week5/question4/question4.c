#include<stdio.h>
#include<string.h> 
#include "lex.yy.c"

struct token *t_ptr ; 

int aterm() ; 
int list() ; 
int lexp() ; 
int lexp_seq1() ; 
int lexp_seq() ; 

struct token *get_next() { 
	struct token *temp = yylex() ; 
	if (!temp)
		return NULL ; 
	return temp ; 
}

int aterm() {
	printf(" In aterm\n");
	if ( (t_ptr && t_ptr->type == NUMERICAL ) || (t_ptr && t_ptr->type == IDENTIFIER)) {
		t_ptr = get_next() ; 
		return 1 ; 
	}
	return 0 ; 
}

int list() {
	printf(" In list\n");
	if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
		t_ptr = get_next() ; 
		if ( lexp_seq() == 1 )  {
			printf(" back in list \n");
			if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
				t_ptr = get_next() ; 
				return 1 ; 
			}
		}

	}
	return 0 ; 
}


int lexp()  {	
	printf(" In lexp\n");
	if ( aterm() == 1 )
		return 1 ; 
	printf(" back in lexp\n" );
	if ( list() == 1)
		return 1 ; 
	printf(" back in lexp \n");
	return 0 ; 
}

int lexp_seq1() {
	int retval ; 
	printf(" In lexp_seq1\n");
	if (lexp() == 1 )  {
		printf(" back in lexp_seq1 \n");
		return lexp_seq1() ; 
	}
	return 1 ; 
}

int lexp_seq() {
	printf(" In lexp_seq\n");
	int retval ; 
	if ( lexp() == 1 )  {
		printf(" back in lexp_seq \n");
		return lexp_seq1() ; 
	}
	return 0 ; 	
}






int main() {

	yyin = fopen("test.c" , "r") ; 
	t_ptr = get_next() ; 
	printf("%s\n",t_ptr->lexeme );
	int retval = lexp() ; 
	if ( retval == 1 )
		printf(" Accept\n");
	else 
		printf(" Reject \n");

}