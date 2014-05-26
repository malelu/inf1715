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
	NodeFunc* funcCall = NULL ; 
	NodeCte* cte ;
	
	/* imprime as strings */
	while(func != NULL)
	{
		StringCte* str = func->firstStringCte ;
		while(str != NULL)
		{
			fprintf(stdout, "\tstring %s = %s\n", str->op1, str->op2);
			str = str->nextNode ;
		}

		func = func->nextFunc ;
	}

	/* imprime as globais */
	func = tab->firstNode ;
	while(func != NULL)
	{
		if(func->global != NULL)
			fprintf(stdout, "\tglobal %s\n", func->global);

		func = func->nextFunc ;
	}

	func = tab->firstNode ;
	while(func != NULL)
	{
		if(func->funcName != NULL)
		{
			fprintf(stdout, "\tfun %s (", func->funcName);
			while(func->params[cont] != NULL)
			{
				fprintf(stdout, "%s", func->params[cont]);
				if(func->params[cont+1] != NULL)
					fprintf(stdout, ", ");
				cont++ ;
			}
			fprintf(stdout, ")\n");

			cte = func->firstCte ;
			while(cte != NULL)
			{
				if(cte->label != NULL)				
					fprintf(stdout, "%s: ", cte->label);

				if(cte->operand != NULL)
				{
					if(strcmp(cte->operand, "if false") == 0 || strcmp(cte->operand, "else if false") == 0)
					{
						fprintf(stdout, "\tiffalse %s goto %s\n", cte->op1, cte->op2);
					}
					if(strcmp(cte->operand, "if") == 0)
					{
						fprintf(stdout, "\tif %s goto %s\n", cte->op1, cte->op2);
					}
					else if(strcmp(cte->operand, "call") == 0)
					{
						fprintf(stdout, "\t%scall %s\n", cte->op2, cte->op1);
					}
					else if(strcmp(cte->operand, "declvar") == 0)
					{
						fprintf(stdout, "\t%s = 0\n", cte->op1);
					}
					else if(strcmp(cte->operand, "goto") == 0)
					{
						fprintf(stdout, "\tgoto %s\n", cte->op1);
					}
					else if ((strcmp(cte->operand, ">") == 0) || (strcmp(cte->operand, "<") == 0) || 
						(strcmp(cte->operand, "+") == 0) || (strcmp(cte->operand, "-") == 0) || 
						(strcmp(cte->operand, "*") == 0) || (strcmp(cte->operand, "/") == 0)
						|| (strcmp(cte->operand, "GE") == 0) || (strcmp(cte->operand, "NE") == 0)
						|| (strcmp(cte->operand, "EQ") == 0))
					{
						fprintf(stdout, "\t%s = %s %s %s\n", cte->op1, cte->op2, cte->operand, cte->op3);
					}
					else if (strcmp(cte->operand, "=") == 0) 
					{
						if(cte->op2[0] != 'n' && cte->op3 != NULL)  /* imprime atrib a char, sem o new */
							fprintf(stdout, "\t%s %s %s %s\n", cte->op1, cte->operand, cte->op3, cte->op2);
						else if(cte->op2[0] == 'n' && cte->op3 != NULL)  /* imprime atrib a char, com o new */
						{
							int cont = 4 ;
							char* number = malloc(20) ;
							while(cte->op2[cont] != '\0')
							{
								number[cont-4] = cte->op2[cont] ;
								cont++ ;
							}
							fprintf(stdout, "\t%s %s new %s %s\n", cte->op1, cte->operand, cte->op3, number);
						}
						else
							fprintf(stdout, "\t%s %s %s\n", cte->op1, cte->operand, cte->op2);
					}
					else if (strcmp(cte->operand, "and") == 0) 
					{
						fprintf(stdout, "\t%s %s %s\n", cte->op1, cte->operand, cte->op2);
					}
					else if (strcmp(cte->operand, "ret") == 0) 
					{
						if(cte->op1 == NULL)
							fprintf(stdout, "\tret\n");
						else
							fprintf(stdout, "\tret %s\n", cte->op1);
					}
				}
				cte = cte->nextNode ;
			}
		}
		func = func->nextFunc ;
		fprintf(stdout, "\n");
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
	yyin = fopen(argv[1], "r");
	yyparse();

	prettyPrinter(programa) ;
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

