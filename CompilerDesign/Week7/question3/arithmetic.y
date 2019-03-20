%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token NL ID NUMBER PLUS MINUS MUL DIV
%left '*' '/' '+' '-'

%%
stmt : exp NL
	;
exp : exp PLUS term
	| exp MINUS term
	| exp MUL term
	| exp DIV term
	|term
	;
term : ID
	 | NUMBER
	 ;
%%
int yyerror(char *msg)
{
	printf("Invalid expression\n");
	return 1;
}
void main()
{
	printf("Enter the expression: \n");
	yyin=fopen("test.txt","r");
	do
	{
		if(yyparse())
		{
			printf("Failure\n");
			exit(0);
		}
	}while(!feof(yyin));
	printf("Success\n");
}
