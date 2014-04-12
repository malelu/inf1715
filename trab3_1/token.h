#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
	char* cValue;
	int iValue;
	int line ;
} Token ;

#define YYSTYPE Token

#endif
