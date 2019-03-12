%{
	int compound = 0 ; 
	int simple = 0 ; 
	
%}
%%
.*(" and "|." or ").*\n {compound++ ; printf("\n Compound - ");  puts(yytext); }
.*\n {simple++; printf("\n Simple - "); puts(yytext) ;  }
%%
int main() {
	yylex() ; 
	printf(" Simple - %d , Compound - %d  \n", simple, compound) ; 
	return 0 ; 
}
int yywrap() {
	return 1 ; 
}