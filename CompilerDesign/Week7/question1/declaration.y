%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
	extern FILE *yyin;
%}

%token ID NUMBER CO SC OB CB DT


%%
dec : DT idl SC 
     |
     ;
idl : ID
     | ID CO idl
     | ID OB NUMBER CB idl
     | ID OB NUMBER CB 
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
	printf("Success\n");
} 
