%{
	int scans = 0 ; 
	int prints = 0 ; 
	
%}
%%
printf {prints++ ; fputs("WRITE" , yyout) ;}
scanf {scans++ ; fputs("READ" , yyout) ;}
[.\n] {fputs(yytext , yyout); }
%%
int main(int argc,char **argv) {
	if (argc < 3) {
		printf(" To run : ./run input.c output.c ");
		exit(0) ; 
	}
	yyin=fopen(argv[1],"r");
	yyout = fopen(argv[2], "w") ; 
	yylex() ; 
	printf(" scans - %d , prints - %d  \n", scans ,prints) ; 
	return 0 ; 
}
int yywrap() {
	return 1 ; 
}