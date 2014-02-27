#include <stdio.h>

enum token { TK_CHAR = 256,
	     TK_INT,
	     TK_STRING,
	     TK_BOOL,
	     TK_TRUE,
	     TK_FALSE,
	     TK_NOT,  
	     TK_WHILE,
	     TK_LOOP, 
	     TK_IF, 
	     TK_ELSE,
	     TK_END, 
	     TK_NEW, 
	     TK_RET, 
	     TK_FUN, 
	     TK_GE,
	     TK_LE, 
	     TK_EE,
	     TK_NE, 
	     TK_AND, 
	     TK_OR, 
	     TK_NUMINT, 
	     TK_NUMFLOAT, 
	     TK_ID, 
	     TK_LITERAL_STRING, 
	     OTHER
};

union Valor{
	char* cValor;
	int iValor;
	double fValor;
}val;

