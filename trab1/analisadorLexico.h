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
	     TK_OPEN_PARENTHESIS,
	     TK_CLOSE_PARENTHESIS,
	     TK_COMMA,
	     TK_COLLON,
	     TK_GREATER,
	     TK_LESS, 
	     TK_GREATER_EQUAL,
	     TK_LESS_EQUAL, 
	     TK_EQUAL,
	     TK_NOT_EQUAL,
	     TK_OPEN_BRACKET,
	     TK_CLOSE_BRACKET,
	     TK_PLUS,
	     TK_MINUS,
	     TK_TIMES,
	     TK_DIVIDED, 
	     TK_AND, 
	     TK_OR, 
	     TK_NUMINT, 
	     TK_ID, 
	     TK_LITERAL_STRING, 
	     ERROR
};

union Valor{
	char* cValor;
	int iValor;
	double fValor;
}val;

