#ifndef TOKEN_H
#define TOKEN_H

#include "ast.h"

typedef struct {
	char* cValue;
	int iValue;
	int line ;
	AST* node ;
} Token ;

#define YYSTYPE Token

#endif
