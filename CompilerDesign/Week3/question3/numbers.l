%{
	int pos_int = 0 ; 
	int neg_int = 0 ; 
	int pos_float = 0 ; 
	int neg_float = 0 ; 
%}
%% 
-0*[1-9][0-9]* {neg_int++ ; }
\+?0*[1-9][0-9]* {pos_int++ ; }
-0*[1-9][0-9]*\.[0-9]+ {neg_float++ ; }
\+?0*[1-9][0-9]*\.[0-9]+ {pos_float++ ; }

%% 
int main() {
	yylex() ; 
	printf(" Positive floating : %d , Positive Integers : %d , Negative floating : %d , Negative Integers : %d \n", pos_float,pos_int,neg_float,neg_int) ; 
	return 0 ;
}
int yywrap() {
	return 1 ; 
}