
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "grammerc.tab.h"

%}
%%
"#".*"\n" {printf(" Ignore header\n");}
"//".*"\n" {printf("Ignore comments \n ");}
\n|\t|" " {printf(" Ignore lines, tabs \n ");}
[0-9]+ {printf("%s\n",yytext); return NUM;}
"main" {printf("%s\n", yytext); return MAIN;} 
"for" {printf("%s\n", yytext); return FOR;} 
"while" {printf("%s\n", yytext); return WHILE;} 
"if" {printf("%s\n", yytext); return IF;} 
"else" {printf("%s\n", yytext); return ELSE;} 
";" {printf("%s\n",yytext);return SC;}
"," {printf("%s\n",yytext);return CO;}
"int"|"char" {printf("%s\n",yytext);return DT;}
"[" {printf("%s\n",yytext); return OBB;}
"]"	{printf("%s\n",yytext); return CBB;}
"(" {printf("%s\n",yytext); return OB;}
")"	{printf("%s\n",yytext);return CB;}
"{" {printf("%s\n",yytext);return OCB;}
"}"	{printf("%s\n",yytext); return CCB;}
[a-zA-Z]+ {printf("%s\n",yytext); return ID;}
"+" {printf("+\n"); return PLUS;}
"-" {printf("-\n"); return MINUS;}
"*" {printf("*\n"); return MUL;}
"/" {printf("/\n"); return DIV;}
"=" {printf("=\n"); return EQ;}
"<" {printf("<\n"); return LT;}
">" {printf(">\n"); return GT;}
"!" {printf("!\n"); return NOT;}
"%" {printf("%s\n",yytext); return MOD;}
%%
int yywrap()
{
	return 1;
}

