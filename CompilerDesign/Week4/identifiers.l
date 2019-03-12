%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "symTable.h"
	#define YY_DECL struct token *yylex(void) 
	enum tokenType { EOFILE = -1, RELATIONAL , ARITHMETIC , SPECIAL , IDENTIFIER, KEYWORD , NUMERICAL, LITERAL , LOGICAL, SHORTHAND, UNARY , DATATYPE} ; 
	
	struct token {
		char *lexeme ; 
		int index ; 
		unsigned int rowno, colno ; 
		enum tokenType type ; 
	};
	int lineno = 1 , colno = 1 ; 
	struct token *tk ; 
	struct token *allocToken() {
		struct token *tk ; 
		tk = (struct token*)malloc(sizeof(struct token)) ; 
		tk->lexeme = (char*)malloc(sizeof(char)*3) ; 
		tk->index = -1 ; 
		tk->type = EOFILE ; 
		return tk ; 
	}	

	void setTokenArgs(struct token *tk , char *lexeme , int index, int rowno, int colno  , enum tokenType type) {
		if (tk == NULL) 
			return ; 
		strcpy (tk->lexeme , lexeme) ; 
		tk->index = index ; 
		tk->rowno = rowno ; 
		tk->colno = colno ; 
		tk->type = type ; 

	}	
%}
%%

"/*"(.(\n?))*"*/" {
	int i = 0 ; 
	while ( yytext[i] != '\0') {
		if (yytext[i] == '\n') {
			lineno++ ; 
			colno = 1 ; 
		}
		else 
			colno++ ; 
		i++ ; 
	}
}

"#".*"\n" {lineno++ ; colno = 1; }
"//".*"\n" {lineno++ ; colno=1 ; }

(\"(.)*\") {
	tk=allocToken();
	setTokenArgs(tk,"",-1, lineno, colno, LITERAL);
	colno = colno + strlen(yytext) ;  	
	return tk ; 
}

(\'(.)\') {
	tk=allocToken();
	setTokenArgs(tk,"",-1, lineno, colno, LITERAL);
	colno = colno + strlen(yytext) ;  	
	return tk; 
}

\n {lineno++ ; colno = 1;}
\t {colno++;}

("="|">"|"<")"="? {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, RELATIONAL);
	colno = colno + strlen(yytext) ;  
	return tk ; 
	}

"!=" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, RELATIONAL);
	colno = colno + strlen(yytext)  ; 
	return tk ; 
}

("+"|"-"|"*"|"/")^("+"|"-"|"*"|"/") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, ARITHMETIC);
	colno = colno + strlen(yytext)  ; 
	return tk ; 	
}

("&"&?|"|"\|?) {
	tk = allocToken() ; 
	setTokenArgs(tk, yytext , -1 ,lineno, colno , LOGICAL) ; 
	colno = colno + strlen(yytext)  ; 
	return tk ; 
}

("++"|"--"|"&"|"~") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, UNARY);
	colno = colno + strlen(yytext)  ; 
	return tk ;	
}

("+="|"-="|"*="|"\=") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, SHORTHAND);
	colno = colno + strlen(yytext)  ; 
	return tk ;
}

(-0*[1-9][0-9]*)|(\+?0*[1-9][0-9]*)|(-0*[1-9][0-9]*\.[0-9]+)|(\+?0*[1-9][0-9]*\.[0-9]+) {
	tk = allocToken() ; 
	setTokenArgs(tk, yytext , -1, lineno , colno , NUMERICAL) ; 
	colno = colno + strlen(yytext) ; 
	return tk ; 
}



(","|"{"|"}"|";"|"("|")"|"["|"]") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, SPECIAL);
	colno = colno + strlen(yytext)  ; 
	return tk ; 	
}

[^a-zA-Z0-9_]"void"|"int"|"char"|"float"|"boolean"|"double"[^a-zA-Z0-9_] {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, DATATYPE);
	colno = colno + strlen(yytext)  ; 
	return tk ;
}

[^a-zA-Z0-9_]"for"|"if"|"while"|"do"|"return"[^a-zA-Z0-9_] {
	tk = allocToken() ; 
	setTokenArgs(tk, yytext , -1, lineno , colno , KEYWORD) ; 
	colno = colno + strlen(yytext) ; 
	return tk ; 
}

[a-zA-Z_][a-zA-Z_0-9]* {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, IDENTIFIER);
	colno = colno + strlen(yytext)  ; 
	return tk ;
}

%%

struct token * getNextToken() {
	char typeStr[15] ; 
	int hashkey ; 
	while( tk == yylex() ) {
		retString(tk->type , typeStr) ; 
		printf("< %s,%d,%d,%s >\n",tk->lexeme,tk->rowno, tk->colno , typeStr) ; 
		return &tk ; 
	}
	return NULL ;

}

int main(int argc,char **argv) {
	if (argc < 3) {
		printf(" To run : ./run input.c output.c ");
		exit(0) ; 
	}
	yyin=fopen(argv[1],"r");
	yyout = fopen(argv[2],"w") ; 
	
	struct token *prev = NULL , *curr = NULL , *temp  ; 
	int insertedKey ; 
	char *datatype ; 
	int scope = 0 , noOfArgs = 0 ; 
	char args[40] ; 
	while (1) {
		curr = getNextToken() ;
		check_scope(curr , &scope ) ;
		noOfArgs = 0 ; 
		strcpy( args, "") ;

		if (curr->type == IDENTIFIER && prev->type == DATATYPE) ) {
			strcpy(datatype, prev->lexeme) ; 
			while(1) {
				next = getNextToken() ; 
				check_scope(next , &scope) ; 
				if (next->type == SPECIAL) {
					if (strcmp(next->lexeme , ";") == 0 ) {
						INSERT(curr, scope , "  " , datatype , "   " , 0 , find_size(datatype)) ; 
						break ; 
					}


					else if ( strcmp(next->lexeme,",") == 0 ) {
						while(1) {
							temp = getNextToken() ; 
							check_scope(temp , &scope) ; 
							if ( strcmp(temp->lexeme, ";") == 0 )  {
								break ; 
							}
							if (temp->type == IDENTIFIER) { 
								INSERT( curr , scope, "   " , datatype , "   ", 0 , find_size(datatype)) ;  // set scope , datatype, returntype = NULL , noofargs = 0 , args = NULL 
							}
						}						
						
					}
					else if (strcmp(next->lexeme, "(" == 0) {
						while(1) {
							temp = getNextToken() ; 
							check_scope(temp , &scope) ; 
							if ( strcmp(temp->lexeme, ")") == 0 )  {
								break ; 
							}
							if (temp->type == IDENTIFIER) {
								keyFound = SEARCH (temp->lexeme) ; 
								if (keyFound != -1 ) {
									strcat( args, keyFound ) ; 
									strcat( args, "   ") ; 
									noOfArgs++ ;  
								}
							}
						}
						INSERT( curr , scope, datatype , "FUNC" , args, noOfArgs , 0) ;  // function == True , so return type == datatype , and type == func , noofargs, args , scope  
					}
					else if (strcmp(next->lexeme,  "[" == 0)) {
						while(1){
							temp = getNextToken() ; 
							check_scope(temp, &scope ) ;
							if (temp->type == NUMERICAL) {
								INSERT(curr , scope , "   " , datatype , "    ", 0 , find_size(datatype)*atoi(temp->lexeme)) ; 	
							} 
					}
				}
			}
		} 

		prev = curr ; 
	} 
	Display() ; 
	return 0 ; 
}
int yywrap() {
	return 1 ; 
}