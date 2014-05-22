#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "simbolos.h"
#include "ir.h"

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
		fprintf(stdout, "   ");
	}
}

void prettyPrinter(AST* node)
{	
	int i ;

	addTab (numTab) ;
	AST_printAST (node->type) ;
	
	if(node->size != 0)
	{
		for(i=0; i<node->size; i++)
		{
			fprintf(stdout, " []");
		}
	}
	if(node->stringVal != NULL)
		fprintf(stdout, " [%s]", node->stringVal);
	if(node->type == AST_NUMINT)
		fprintf(stdout, " [%d]", node->intVal);

	Symbols_printSYM (node->symbol_type) ;

	if(node->firstChild == NULL)
		fprintf(stdout, " @%d\n", node->line);
	else if(node->firstChild != NULL)
	{	
		fprintf(stdout, " @%d { \n", node->line);
		numTab++ ;
		prettyPrinter(node->firstChild) ;
		addTab (numTab) ;
		fprintf(stdout, " }\n");
	}
	

	if(node->nextSibling != NULL)
		prettyPrinter(node->nextSibling) ;
	else
		numTab--;

}

void dump(IrTable* tab)
{
	int cont = 0 ;
	NodeFunc* func = tab->firstNode ; 
	while(func != NULL)
	{
		fprintf(stdout, "%s (", func->funcName);
		while(func->params[cont] != NULL)
		{
			fprintf(stdout, "%s, ", func->params[cont]);
			cont++ ;
		}
		fprintf(stdout, ")");
		func = func->nextFunc ;
	}
}


void yyerror (const char * s)
{	
	fprintf(stdout, "parser error %s \n",s);
	fprintf(stdout, "Erro de sintaxe na linha %d\n", lineCount);
	error = 1;
}

int main (void)
{
	//yydebug = 1;
	yyparse();

	error = Symbols_annotate(programa) ;
	if (error == 1)
	{
		prettyPrinter(programa) ;
		IrTable* ir = IR_gen(programa) ;
		//dump(ir) ;
	}

	if (error == 0)
		return 0 ;
	else
		return 1 ;
}

