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

void dump(OpTable* tab)
{
	int cont = 0 ;
	NodeFunc* func = tab->firstNode ; 
	NodeCte* cte ;
	while(func != NULL)
	{
		fprintf(stdout, "\t%s (", func->funcName);
		while(func->params[cont] != NULL)
		{
			fprintf(stdout, "%s, ", func->params[cont]);
			cont++ ;
		}
		fprintf(stdout, ")\n");

		cte = func->firstCte ;
		while(cte != NULL)
		{
			if(cte->label != NULL && cte->operand != "none")				
				fprintf(stdout, "%s: ", cte->label);

			if(cte->operand != NULL)
			{
				if(strcmp(cte->operand, "if false") == 0)
				{
					fprintf(stdout, "\tif not %s goto %s\n", cte->op1, cte->op2);
				}
				else if(strcmp(cte->operand, "else if false") == 0)
				{
					fprintf(stdout, "\telse if not %s goto %s\n", cte->op1, cte->op2);
				}
				else if(strcmp(cte->operand, "declvar") == 0)
				{
					fprintf(stdout, "\t%s = 0\n", cte->op1);
				}
				else if(strcmp(cte->operand, "goto") == 0)
				{
					fprintf(stdout, "\tgoto %s\n", cte->op1);
				}
				else
				{
					fprintf(stdout, "\t%s = %s %s %s\n", cte->op1, cte->op2, cte->operand, cte->op3);
				}
			}
			cte = cte->nextNode ;
		}
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
		OpTable* tab = IR_gen(programa) ;
		dump(tab) ;
	}

	if (error == 0)
		return 0 ;
	else
		return 1 ;
}

