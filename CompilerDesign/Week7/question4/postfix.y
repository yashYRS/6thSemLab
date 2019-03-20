%{
	#include <stdio.h>
	#include <stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}
%token NL ID NUMBER PLUS MINUS MUL DIV POW
%left '*' '/' '+' '-'
%right '^'

%%
input : input line
		|
		;

line : NL | exp NL;

exp : NUMBER 
	| exp exp PLUS 
	| exp exp MINUS
	| exp exp MUL
	| exp exp DIV
	| exp exp POW
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
