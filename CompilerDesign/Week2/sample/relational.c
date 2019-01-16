#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
	char c, buf[10] ; 
	FILE *fp = fopen("input.c","r") ; 
	if (fp == NULL ) {
		printf("\n Can't open file ");
		exit(0) ; 
	}
	c = fgetc(fp) ; 
	int i ; 
	while (c!=EOF) {
		i = 0 ; 
		buf[0] = '\0' ; 
		if ( c == '=') {
			buf[i++] = c ; 
			c = fgetc(fp) ; 
			if ( c == '=') {
				buf[i++] = c ;
				buf[i] = '\0' ; 
				printf(" \n Relational Operator : %s",buf );
			}
			else {
				buf[i] = '\0' ;
				printf("\n Assignment operator : %s",buf );
			}
		}
		else {
			if (c == '<' || c == '>' || c == '!') {
				buf[i++] = c; 
				c = fgetc(fp) ; 
				if (c == '=') {
					buf[i++] = c ; 
				}
				buf[i] = '\0' ; 
				printf("\n Relational Operator : %s",buf) ; 
			}
			else 
				buf[i] = '\0' ; 
		}
		c = fgetc(fp) ; 
	}
	return 0 ; 
}