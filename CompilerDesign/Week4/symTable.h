#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TableLength 30 

enum tokenType { EOFILE = -1 , LESS_THAN, LESS_THAN_OR_EQUAL , GREATER_THAN , GREATER_THAN_OR_EQUAL , NOT_EQUAL } ; 

struct token {
	char *lexeme ; 
	int index ; 
	unsigned int rowNo, colNo ; 
	enum tokenType type ; 
} ;
 
struct ListElement {
	struct token *tok ; 
	int noOfArgs ; 
	char args[50] ; 
	int scope ; 
	char retType[20] ;
	char eleType[20] ; 
	struct ListElement *next ; 
	int size ; 
}; 

struct ListElement *TABLE[TableLength] ; 

void initialize() {
	for (int i  = 0 ; i < TableLength ; i++) {
		TABLE[i] = NULL ; 
	}
}

void Display() {
	//iterate through the linked list and display 
	struct ListElement *ele ; 
	printf("KEY , LEXEME , SCOPE , DATATYPE , RETURN TYPE , ARGUMENTS , NO_OF_ARGUMENTS , SIZE \n");
	for (int key = 0 ; key < TableLength ; key++ ) {
		ele = TABLE[key] ; 
		while(ele->next) {
			printf("%d %s  %d  %s  %s %s %d %d \n", key , ele->tok->lexeme , ele->scope , ele->eleType , ele->retType , ele->args , ele->noOfArgs , ele->size );
			ele = ele->next ;   
		}
	} 
}

int HASH( char *str ) {
	int sum = 0 ; 
	for (int i = 0 ; i < strlen(str) ; i++ ) {
		sum = sum + (int) str[i] ; 
	}
	return sum%TableLength ; 
} 

int SEARCH( char *str ) {
	// Write a search routine to check whether a lexeme exists in the Symbol table \
	// 1 if found, else 0
	struct ListElement *ele ; 
	for (int key = 0 ; key < TableLength ; key++ ) {
		ele = TABLE[key] ; 
		while(ele->next) {
			if (strcmp(ele->tok->lexeme , str ) == 0 )
				return key ; 
			ele = ele->next ;   
		}
	} 
	return -1 ; 
}

int INSERT (struct token *tk  , int sc , char *retType, char *idType, char *args, int noOfArgs , int size  ) {
	int hashkey = SEARCH(tk->lexeme) ; 
	if ( hashkey != -1 ) {
		return  hashkey;  // check if element present already 
	}
	hashkey = HASH(tk->lexeme) ; 
	struct ListElement *cur = (struct ListElement*)malloc(sizeof(struct ListElement) ) ; 
	cur->tok = tk ; 
	cur->scope = sc ; 
	strcpy(cur->retType , retType) ; 
	strcpy(cur->eleType , idType) ; 
	strcpy(cur->args , args) ; 
	cur->noOfArgs = noOfArgs ; 
	cur->next = NULL ; 
	cur->size = size ; 

	if (TABLE[hashkey] == NULL) {
		TABLE[hashkey] = cur ; // No collision 
	}
	else {
		struct ListElement *ele = TABLE[hashkey] ;
		while (ele->next != NULL) {
			ele = ele->next ; // Add the element at the end in the case of a collision 
 		}
		ele->next = cur ; 
	}
	return hashkey ; 
}

void check_scope(struct token *tk, int *scope) {
	if ( (strcmp(tk->lexeme , "{") == 0 ) 
		*(scope) = *(scope) + 1 ;
	else if ( (strcmp(tk->lexeme , "}") == 0  ) 
		*scope = *scope - 1 ;
}

int find_size(char *str) {
	if (strcmp(str,"int") == 0)
		return sizeof(int) ; 
	else if (strcmp(str,"char") == 0)
		return sizeof(char) ; 
	else if (strcmp(str, "float") == 0 )
		return sizeof(float) ; 
	else if (strcmp(str, "double") == 0 )
		return sizeof(double) ; 
	else 
		return 0 ; 
}