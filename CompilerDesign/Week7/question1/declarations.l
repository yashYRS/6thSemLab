%{
#include <stdio.h>
#include <stdlib.h>
#include "declaration.tab.h"
%}
%%
";" {printf("%s\n",yytext);return SC;}
"," {printf("%s\n",yytext);return CO;}
"int"|"char" {printf("%s\n",yytext);return DT;}
"[" {return OB;}
"]"	{return CB;}
[a-zA-Z]+ {printf("%s\n",yytext); return ID;}
%%
int yywrap(){
	return 1;
}
