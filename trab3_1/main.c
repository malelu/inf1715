#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int lineCount ;

extern int yydebug;

extern AST* programa ;


void prettyPrinter(AST* node)
{
	printf("oi");
	//printf("%d", node->line);
}

void yyerror (const char * s)
{	
	printf("parser error %s \n",s);
	printf("Erro de sintaxe na linha %d\n", lineCount);
	exit(1);
}

int main (void)
{
	//yydebug = 1;
	yyparse();
	printf ("Nao ha erros de sintaxe\n");	
	prettyPrinter(programa) ;
}
