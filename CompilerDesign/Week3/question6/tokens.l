%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define YY_DECL struct token *yylex(void) 
	enum tokenType { EOFILE = -1, RELATIONAL , ARITHMETIC , SPECIAL , IDENTIFIER, KEYWORD } ; 
	
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

"/*".*"*/" {
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

(\"(.)*\") {colno+=strlen(yytext);}

(\'(.)\') {colno+=strlen(yytext);}

\n {lineno++ ; colno = 1;}

("="|">"|"<")"="? {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, RELATIONAL);
	colno++ ; 
	return tk ; 
	}

"!=" {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, RELATIONAL);
	colno++ ; 
	return tk ; 
}

("+"|"-"|"*"|"/")^("+"|"-"|"*"|"/") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, ARITHMETIC);
	colno++ ; 
	return tk ; 	
}

("{"|"}"|";"|"("|")"|"["|"]") {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, SPECIAL);
	colno++ ; 
	return tk ; 	
}

[^a-zA-Z0-9_]"printf"|"scanf"|"int"|"char"|"return"|"for"|"if"|"else"[^a-zA-Z0-9_] {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, KEYWORD);
	colno++ ; 
	return tk ;
}

[a-zA-Z_][a-zA-Z_0-9]* {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, IDENTIFIER);
	colno++ ; 
	return tk ;
}

%%
int main(int argc,char **argv) {
	if (argc < 2) {
		printf(" To run : ./run input.c ");
		exit(0) ; 
	}
	yyin=fopen(argv[1],"r");
	while(tk == yylex())
		printf("\n Row : %d , Col : %d, Type :  %d, Lex :  %s \n",tk->rowno,tk->colno,tk->type ,tk->lexeme );
	return 0 ; 
}
int yywrap() {
	return 1 ; 
}