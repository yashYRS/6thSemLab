%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token OCB CCB OB CB OBB CBB SC CO DT NUM EQ LT GT NOT MOD IF ELSE FOR WHILE PLUS MINUS MUL DIV ID NL 


%%

decisionstat : IF OB expn CB OCB statementlist CCB dprime
	; 

statementlist : statement statementlist 
	| 
	; 

statement : assignstat SC 
	| decisionstat 
	; 

assignstat : ID EQ expn 
	; 

expn : simple eprime 
	; 

eprime : relop simple
	| 
	; 

simple : term seprime 
	; 

seprime : addop term seprime 
	| 
	; 

term : factor tprime 
	; 

tprime : mulop factor tprime 
	| 
	; 

factor : ID 
	| NUM 
	; 



dprime : ELSE OCB statementlist CCB 
	| 
	 ; 


relop : EQ EQ 
	| NOT EQ 
	| LT EQ 
	| GT EQ 
	| LT 
	| GT 
	; 

addop : PLUS 
	| MINUS
	; 

mulop : MUL	
	| DIV 
	| MOD 
	; 

 
%%

int yyerror(char *msg)
{
	printf("Invalid Expression\n");
	return 1;
}

void main()
{
	printf("Enter the expression\n");
	yyin=fopen("test.txt","r");

	do {
		if(yyparse()) {
			  printf("\nFailure");
			  exit(0);
     		}
	}while(!feof(yyin));
	printf("Success \n");
} 
