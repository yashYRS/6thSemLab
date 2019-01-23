%{
	int chars = 0 ; 
	int words = 0 ; 
	int lines = 0 ; 
	int blanks = 0 ; 
%}

%% 
[a-zA-Z]+ {words++ ; chars += strlen(yytext) ; }
\n {chars++ ; lines++ ; }
[ ] {blanks++ ; }
. {chars++ ;} 

%% 
int main() {
	yylex() ; 
	printf(" lines : %d , words : %d , chars : %d , blanks : %d \n", lines , words , chars , blanks) ; 
	return 0 ;
}
int yywrap() {
	return 1 ; 
}