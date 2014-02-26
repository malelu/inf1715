#include <stdio.h>

enum token { TK_CHAR = 256,
	     TK_INT, 
	     TK_FLOAT, 
	     TK_WHILE, 
	     TK_IF, 
	     TK_ELSE, 
	     TK_NEW, 
	     TK_RET, 
	     TK_VOID, 
	     TK_GE,
	     TK_LE, 
	     TK_EE,
	     TK_NE, 
	     TK_AND, 
	     TK_OR, 
	     TK_NUMINT, 
	     TK_NUMFLOAT, 
	     TK_ID, 
	     TK_STRING, 
	     TK_SYMBOL
};

union Valor{
	char* cValor;
	int iValor;
	double fValor;
}val;

