#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lex.yy.c"

struct token *t_ptr ; 

struct token *get_next() { 
	struct token *temp = yylex() ; 
	if (!temp)
		return NULL ; 
	return temp ; 
}

int program_construct() ;
void error_func() ; 
int declarations_construct() ; 
int datatype_construct() ; 
int identifier_list() ; 
int statement_list() ; 
int statement_construct() ; 
int assign_stat() ; 
int expn() ; 
int dprime() ; 
int factor() ; 
int eprime() ; 
int term_construct() ; 
int simple_exp() ; 
int seprime() ; 
int tprime() ; 
int decision_stat() ; 
int looping_stat() ; 
int relop() ; 
int addop() ; 
int mulop() ;  


void error_func() {
	printf(" Error at %d line %d column %s \n ",t_ptr->rowno , t_ptr->colno , t_ptr->lexeme);
	exit(0) ; 
}

int program_construct() {
	printf("\n IN program " ) ; 
	if ( t_ptr && strcmp(t_ptr->lexeme,"main") == 0 ) {
		printf("\n Main matched " ) ; 
		t_ptr = get_next();
		if ( t_ptr && strcmp(t_ptr->lexeme,"(") == 0 ) {
			printf("\n ( matched " ) ; 
			t_ptr = get_next() ; 
			if ( t_ptr && strcmp(t_ptr->lexeme,")") == 0 ) { 
				printf("\n ) matched " ) ; 
				t_ptr = get_next() ; 
				if ( t_ptr && strcmp(t_ptr->lexeme,"{") == 0 ) {
					printf("\n { matched " ) ; 
					t_ptr = get_next() ; 
					if ( declarations_construct() == 1 ) {		
						printf( " \n back to program ") ; 
						if ( statement_list() == 1 ) {
							printf( " \n back to program ") ; 
							if ( t_ptr && strcmp(t_ptr->lexeme,"}") == 0 ) {
								printf( " \n } matched ") ; 
								t_ptr = get_next() ; 
								return 1 ; ;
							}
						}
					}
				}
			}
		}
	}
	return 0 ; 
}

int declarations_construct() {
	printf( "\n In declarations " ) ; 
	if ( datatype_construct() == 1) {
		printf( "\n back to declarations ") ; 
		if (identifier_list() == 1 ) {
			printf("\n back to declarations " ) ; 
			if (t_ptr && strcmp(t_ptr->lexeme , ";" )== 0 ) {
				printf("\n matched ; " ) ; 
				t_ptr = get_next() ; 
				return declarations_construct() ;
			}
		}
		else
			error_func() ; 
	}

	return 1 ; 
}

int datatype_construct() {
	printf("\n in datatype ") ; 
	if ( t_ptr && (strcmp(t_ptr->lexeme, "int") == 0  || strcmp(t_ptr->lexeme, "char") == 0 )) {
		t_ptr = get_next() ; 
		printf( "\n matched some datatype " ); 	
		return 1 ; 
	}
		
	return 0 ; 
}

int identifier_list() {
	printf( " \n in identifier list " ) ; 
	if ( t_ptr && t_ptr->type == IDENTIFIER ) {
		t_ptr = get_next() ; 
		printf( " \n Matched some identifier " ) ; 
		if ( t_ptr && strcmp(t_ptr->lexeme , ",") == 0 ) {
			printf( " \n Matched , " ) ; 
			t_ptr = get_next() ; 
			return identifier_list() ; 
		}
		else if ( t_ptr && strcmp(t_ptr->lexeme , "[" ) == 0) {
			printf( " \n Matched [" ) ; 
			t_ptr = get_next() ; 
			if ( t_ptr && t_ptr->type == NUMERICAL ) {
				printf( " \n Matched some number " ) ; 
				t_ptr = get_next() ; 
				if ( t_ptr && strcmp(t_ptr->lexeme , "]") == 0 ) {
					printf( " \n Matched ] " ) ; 
					if ( t_ptr && strcmp(t_ptr->lexeme , ",") == 0 ) {
						printf( " \n Matched , " ) ; 
						t_ptr = get_next() ; 
						return identifier_list() ; 
					}
				}
				return 1 ; 
			}
		}
		return 1 ; 
	}
	error_func() ; 
}

int statement_list() {
	printf("\nIn statement list ") ; 
	if ( statement_construct() == 1 ) {
		printf( "\n back to statement list ") ; 
		return statement_list() ; 
	}
	return 1 ; 
}

int statement_construct() {
	printf(" \n In statement " ) ; 
	if ( looping_stat() == 1 || decision_stat() == 1 ) { 
		return 1 ; 
	}
	printf( "\n back to statement ") ;
	if (assign_stat() == 1)  {
		printf( "\n back to statement ") ;
		if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
			printf( "\n matched ;  ") ;
			t_ptr = get_next() ; 
			return 1 ;
		}	
	}
	return 0 ; 
}

int assign_stat() {
	printf( "\n In assignment ") ;
	if ( t_ptr && t_ptr->type == IDENTIFIER ) {
		printf( "\n matched some identifier ") ;
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "=") == 0 ) {
			printf( "\n matched equals ") ;
			t_ptr = get_next() ; 
			return expn() ; 
		}
	}
	return 0 ;
}

int expn() {
	printf( " \n In expn ") ; 
	if ( simple_exp() == 1)  {
		printf( " \n back to expn ") ; 
		return eprime() ; 
	}
	return 0 ; 
}

int eprime() {
	printf( " \n In eprime ") ; 
	if ( relop() == 1 )   {
		printf( " \n back to relop ") ; 
		return simple_exp() ; 	
	}
	return 1 ; 
}

int simple_exp() {
	printf( "\n In simple expn ") ;
	if (term_construct() == 1)  {
		printf( "\n back to simple expn ") ; 
		return seprime() ; 
	}
}

int seprime() {
	printf( " \n In seprime" ) ; 
	if ( addop() == 1 ) {
		printf( " \n back to seprime ") ; 
		if (term_construct() == 1) {
			printf( " \n back to seprime" ) ; 		
			return seprime() ; 
		}
		error_func() ; 
	}
	return 1 ;
}

int term_construct() {
	printf( "\n In term ") ;
	if ( factor() == 1 ) {
		printf( "\n back to term ") ;
		return tprime() ; 	
	}
}

int tprime() {
	printf( " \n In tprime " ) ; 
	if ( mulop() == 1 ) {
		printf( "\n back to tprime ") ;
		if ( factor() == 1 ) {
			printf( "\n back to tprime ") ;
			return tprime() ; 	
		}
	}
	return 1 ; 
}

int factor() {
	printf( "\n In factor ") ;
	if (t_ptr && (t_ptr->type == IDENTIFIER || t_ptr->type == NUMERICAL  ) )  {
		t_ptr = get_next() ; 
		printf( "\n matched some number or identifier ") ;	
		return 1 ; 		
	}
}

int decision_stat() {
	printf( "\n In decision ") ;
	if (t_ptr && strcmp(t_ptr->lexeme , "if") == 0 ) {
		printf( "\n if matched ") ;
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			printf( "\n ( matched ") ;
			t_ptr = get_next() ; 
			if ( expn() == 1 )  {
				printf( "\n back to decision ") ;
				if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
					printf( "\n ) matched ") ;
					t_ptr = get_next()  ; 
					if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
						printf( "\n } matched ") ;
						t_ptr = get_next() ; 
						if ( statement_list() == 1) {
							printf( "\n back to decision ") ;
							if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
								printf( "\n } matched ") ;
								t_ptr = get_next() ; 
								return dprime() ; 
							}

						}
					}
				}

			}

		}
	}
	return 0 ; 
}

int dprime() {
	printf( "\n In dprime ") ;
	if (t_ptr && strcmp(t_ptr->lexeme , "else") == 0 ) {
		printf( "\n matched else ") ;
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
			printf( " \n matched { " ) ; 
			t_ptr = get_next() ; 
			if ( statement_list() == 1 ) {
				printf( "\n back to dprime ") ;
				if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
					printf( "\n } matched ") ;
					t_ptr = get_next() ; 
					return 1 ; 
				}
			}
		}
	}
	return 1 ; 
}

int looping_stat() {
	printf( "\n in loop ") ; 
	if (t_ptr && strcmp(t_ptr->lexeme , "while") == 0 ) {
		printf( " \n matched while ") ; 
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			printf( " \n matched ( ") ;
			if (expn() == 1) {
				printf( "\n back to loop ") ;
				if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
					printf( " \n matched ) ") ;
					t_ptr = get_next() ; 
					if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
						printf( " \n matched { ") ;
						t_ptr = get_next() ; 
						if ( statement_list() == 1 ) {
							printf( " \n back to loop ") ;
							if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
								printf( " \n matched } ") ;
								t_ptr = get_next() ; 
								return 1 ; 
							}
						}
					}
				}
			}
		}
	}
	if (t_ptr && strcmp(t_ptr->lexeme , "for") == 0 ) {
		printf( " \n matched for ") ;
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			printf( " \n matched ( ") ;
			t_ptr = get_next() ; 
			if ( assign_stat() == 1) {
				printf(" \n back to loop " ) ; 
				if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
					t_ptr = get_next() ;
					printf( " \n matched ;  ") ; 
					if ( expn() == 1) {
						printf(" \n back to loop " ) ; 
						if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
							printf( " \n matched ; ") ;
							t_ptr = get_next() ; 
							if ( assign_stat() == 1) {
								printf(" \n back to loop " ) ; 
								if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
									printf( " \n matched ) ") ;
									t_ptr = get_next() ; 
									if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
										printf( " \n matched { ") ;
										t_ptr = get_next() ; 
										if ( statement_list() == 1 ) {
											printf( " \n back to loop ") ;
											if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
												printf( " \n matched } ") ;
												t_ptr = get_next() ; 
												return 1 ; 
											}
										}
									} 
								}
							}

						}
					}
				}
			}
		}
	}
	return 0 ; 
}

int relop() {
	printf( " \n in relop ") ; 
	if ( t_ptr && t_ptr->type == RELATIONAL ) {
		printf( " \n matched some relational ") ; 
		t_ptr = get_next() ; 
		return 1 ; 
	}
	return 0 ; 
}

int addop() {	
	printf( " \n in addop ") ; 
	if ( t_ptr && (strcmp(t_ptr->lexeme , "+") == 0 || strcmp(t_ptr->lexeme , "-") == 0 )) {
		printf( " \n matched  +/-" ) ; 
		t_ptr = get_next() ; 
		return 1 ; 
	}
	return 0 ; 
}

int mulop() {
	printf( "\n in mulop " ) ; 
	if ( t_ptr && (strcmp(t_ptr->lexeme , "*") == 0 || strcmp(t_ptr->lexeme , "/") == 0 || strcmp(t_ptr->lexeme , "%") == 0 ))	 {
		printf( " \n matched some mulop ") ; 
		t_ptr = get_next() ; 
		return 1; 
	}
	return 0 ; 
}

int main() {

	yyin = fopen("test.c" , "r") ; 
	t_ptr = get_next() ; 
	if ( program_construct() == 1) 
		printf(" Accept\n");
	else 
		printf(" Reject \n");

} 
