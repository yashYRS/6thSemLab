//This is a single line comment 
/* ******** This i s a 
******* Mul      tiple line comment 
**** */
#include<stdio.h>
void main() {
	FILE    *fopen() ,   *fp ; 
	int c ; 
	fp = fopen("prog.c","r") ; //    omment 
	c = getc(fp) ; 
	while ( c != EOF ) {
		putchar(c) ; 
		c    =    getc(fp) ; 
	} /* Multiline 
	comment */
	fclose(fp) ; 
}