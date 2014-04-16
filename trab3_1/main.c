#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int lineCount ;
extern int yydebug;
extern AST* programa ;
extern int numTab = 0 ;
extern int error = 0 ;

void addTab (int numTab)
{
	int cont;
	for(cont=0;cont<numTab;cont++)
	{
		fprintf(stderr, "   ");
	}
}


void prettyPrinter(AST* node)
{	

	addTab (numTab) ;
	printAST (node->type) ;

	if(node->stringVal != NULL)
		fprintf(stderr, " [%s]", node->stringVal);
	if(node->type == AST_NUMINT)
		fprintf(stderr, " [%d]", node->intVal);

	if(node->firstChild == NULL)
		fprintf(stderr, " @%d\n", node->line);
	else if(node->firstChild != NULL)
	{	
		fprintf(stderr, " @%d { \n", node->line);
		numTab++ ;
		prettyPrinter(node->firstChild) ;
		addTab (numTab) ;
		fprintf(stderr, " }\n");
	}

	if(node->nextSibling != NULL)
		prettyPrinter(node->nextSibling) ;
	else
		numTab--;

}


void yyerror (const char * s)
{	
	printf("parser error %s \n",s);
	printf("Erro de sintaxe na linha %d\n", lineCount);
	error = 1;
}

int main (void)
{
	//yydebug = 1;
	yyparse();
	//fprintf(stderr, "Nao ha erros de sintaxe\n");
	prettyPrinter(programa) ;
	if (error == 0)
		return 0 ;
	else
		return 1 ;
}

