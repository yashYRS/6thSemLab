%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define YY_DECL struct token *yylex(void) 
	enum tokenType { EOFILE = -1, RELATIONAL , ARITHMETIC , SPECIAL , IDENTIFIER, KEYWORD , NUMERICAL, LITERAL , LOGICAL, SHORTHAND, UNARY } ; 
	
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

[^a-zA-Z0-9_]"int"|"char"|"return"|"for"|"if"|"else"[^a-zA-Z0-9_] {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, KEYWORD);
	colno = colno + strlen(yytext)  ; 
	return tk ;
}

[a-zA-Z_][a-zA-Z_0-9]* {
	tk=allocToken();
	setTokenArgs(tk,yytext,-1, lineno, colno, IDENTIFIER);
	colno = colno + strlen(yytext)  ; 
	return tk ;
}

%%

void retString(enum tokenType type, char *retStr) {
	if (type == RELATIONAL) 
		strcpy(retStr, "RELATIONAL") ; 
	else if (type == ARITHMETIC) 
		strcpy(retStr , "ARITHMETIC") ; 
	else if (type == KEYWORD)
		strcpy(retStr , "KEYWORD") ; 
	else if (type == IDENTIFIER) 
		strcpy(retStr , "IDENTIFIER") ; 
	else if (type == SPECIAL) 
		strcpy(retStr , "SPECIAL") ;
	else if (type == NUMERICAL) 
		strcpy(retStr, "NUMERICAL")  ; 
	else if (type == LOGICAL) 
		strcpy(retStr , "LOGICAL") ; 
	else if (type == LITERAL) 
		strcpy(retStr, "LITERAL") ; 
	else if (type == UNARY)  
		strcpy(retStr,"UNARY") ; 
	else if (type == SHORTHAND) 
		strcpy(retStr,"SHORTHAND") ; 
		
}

int prompt() {
	printf(" \n\n Choose - 1. getNextToken 2. Exit ") ; 
	int a; 
	scanf("%d",&a) ; 
	return a ;
}
void getNextToken() {
	char typeStr[15] ; 
	while( tk == yylex() ) {
		retString(tk->type , typeStr) ; 
		printf("< %s,%d,%d,%s >\n",tk->lexeme,tk->rowno, tk->colno , typeStr) ;
		fprintf(yyout,"< %s,%d,%d,%s >\n",tk->lexeme,tk->rowno, tk->colno , typeStr) ; 
		return ; 
	}
	exit(0) ; 

}

int main(int argc,char **argv) {
	if (argc < 3) {
		printf(" To run : ./run input.c output.c ");
		exit(0) ; 
	}
	yyin=fopen(argv[1],"r");
	yyout = fopen(argv[2],"w") ; 
	int flag = 1 ; 
	while(flag) {
		switch( prompt() ) {
			case 1 : getNextToken() ; break ; 
			case 2 : flag = 0 ; break ; 
		}
	}
	return 0 ; 
}
int yywrap() {
	return 1 ; 
}