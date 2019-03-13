#include<stdio.h>
#include<string.h>
#include "lex.yy.c"

struct token *t_ptr ; 

struct token *get_next() { 
	struct token *temp = yylex() ; 
	if (!temp)
		return NULL ; 
	return temp ; 
}

void error_func() {
	printf(" Error at %d line %d column\n",t_ptr->rowno , t_ptr->colno );
}

int program_construct() {
	if ( t_ptr && strcmp(t_ptr->lexeme,"main") == 0 ) {
		t_ptr = get_next();
		if ( t_ptr && strcmp(t_ptr->lexeme,"(") == 0 ) {
			t_ptr = get_next() ; 
			if ( t_ptr && strcmp(t_ptr->lexeme,")") == 0 ) { 
				t_ptr = get_next() ; 
				if ( t_ptr && strcmp(t_ptr->lexeme,"{") == 0 ) {
					t_ptr = get_next() ; 
					if ( declarations_construct() == 1 ) {		
						if ( statement_list() == 1 ) {
							if ( t_ptr && strcmp(t_ptr->lexeme,"}") == 0 ) {
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
	if ( datatype_construct() == 1) {
		if (identifier_list == 1 ) {
			if (t_ptr && strcmp(t_ptr->lexeme , ";" )== 0 ) {
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
	if ( t_ptr && (strcmp(t_ptr->lexeme, "int") == 0  || strcmp(t_ptr->lexeme, "char") == 0 ))
		return 1 ; 
	error_func() ; 
}

int identifier_list() {
	if ( t_ptr && strcmp(t_ptr->lexeme, "id") == 0 ) {
		if ( t_ptr && strcmp(t_ptr->lexeme , ",") == 0 ) {
			t_ptr = get_next() ; 
			return identifier_list() ; 
		}
		else if ( t_ptr && strcmp(t_ptr->lexeme , "[" ) == 0) {
			t_ptr = get_next() ; 
			if ( t_ptr && t_ptr->type == NUMERICAL ) {
				t_ptr = get_next() ; 
				if ( t_ptr && strcmp(t_ptr->lexeme , "]") == 0 ) {
					if ( t_ptr && strcmp(t_ptr->lexeme , ",") == 0 ) {
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
	if ( statement_construct() == 1 )
		return statement_list() ; 
	return 1 ; 
}

int statement_construct() {
	if ( looping_stat() == 1 || decision_stat() == 1 )
		return 1 ; 
	if (assign_stat() == 1) 
		if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
			t_ptr = get_next() ; 
			return 1 ;
		}
	error_func() ; 
}

int assign_stat() {
	if (t_ptr && strcmp(t_ptr->lexeme , "id") == 0 ) {
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "=") == 0 ) {
			t_ptr = get_next() ; 
			return expn() ; 
		}
	}
	error_func() ; 
}

int expn() {
	if ( simple_exp() == 1) 
		return eprime() ; 
	error_func() ; 
}

int eprime() {
	if ( relop() == 1 )  
		return simple_exp() ; 
	return 1 ; 
}

int simple_exp() {
	if (term_construct() == 1) 
		return seprime() ; 
}

int seprime() {
	if ( addop() == 1 ) {
		if (term_construct() == 1) 
			return seprime() ; 
		error_func() ; 
	}
	return 1 ;
}

int term_construct() {
	if ( factor() == 1 )
		return tprime() ; 
}

int tprime() {
	if ( mulop() == 1 ) {
		if ( factor() == 1 )
			return tprime() ; 
	}
	return 1 ; 
}

int factor() {
	if (t_ptr && (strcmp(t_ptr->lexeme , "id") == 0 || t_ptr->type == NUMERICAL  ) ) 
		return 1 ; 		
}

int decision_stat() {
	if (t_ptr && strcmp(t_ptr->lexeme , "if") == 0 ) {
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			t_ptr = get_next() ; 
			if ( expn() == 1 )  {
				if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
					t_ptr = get_next()  ; 
					if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
						t_ptr = get_next() ; 
						if ( statement_list() == 1) {
							if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
								t_ptr = get_next() ; 
								return dprime() ; 
							}

						}
					}
				}

			}

		}
	}
	error_func() ; 
}

int dprime() {
	if (t_ptr && strcmp(t_ptr->lexeme , "else") == 0 ) {
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
			t_ptr = get_next() ; 
			if ( statement_list() == 1 ) {
				if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
					t_ptr = get_next() ; 
					return 1 ; 
				}
			}
		}
	}
	return 1 ; 
}

int looping_stat() {
	if (t_ptr && strcmp(t_ptr->lexeme , "while") == 0 ) {
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			if (expn() == 1) {
				if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
					t_ptr = get_next() ; 
					if (t_ptr && strcmp(t_ptr->lexeme , "{") == 0 ) {
						t_ptr = get_next() ; 
						if ( statement_list() == 1 ) {
							if (t_ptr && strcmp(t_ptr->lexeme , "}") == 0 ) {
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
		t_ptr = get_next() ; 
		if (t_ptr && strcmp(t_ptr->lexeme , "(") == 0 ) {
			t_ptr = get_next() ; 
			if ( assign_stat() == 1) {
				if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
					t_ptr = get_next() ; 
					if ( expn() == 1) {
						if (t_ptr && strcmp(t_ptr->lexeme , ";") == 0 ) {
							t_ptr = get_next() ; 
							if ( assign_stat() == 1) {
								if (t_ptr && strcmp(t_ptr->lexeme , ")") == 0 ) {
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
	error_func() ; 
}

int relop() {
	if ( t_ptr && t_ptr->type == RELATIONAL ) {
		t_ptr = get_next() ; 
		return 1 ; 
	}
	error_func() ; 
}

int addop() {	
	if ( t_ptr && (strcmp(t_ptr->lexeme , "+") == 0 || strcmp(t_ptr->lexeme , "-") == 0 )) {
		t_ptr = get_next() ; 
		return 1 ; 
	}
	error_func() ; 
}

int mulop() {
	if ( t_ptr && (strcmp(t_ptr->lexeme , "*") == 0 || strcmp(t_ptr->lexeme , "/") == 0 || strcmp(t_ptr->lexeme , "%") == 0 ))	 {
		t_ptr = get_next() ; 
		return 1; 
	}
	error_func() ; 
}

int main() {

	yyin = fopen("test.c" , "r") ; 
	t_ptr = get_next() ; 
	if ( program_construct() == 1) 
		printf(" Accept\n");
	else 
		printf(" Reject \n");

} 