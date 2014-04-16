#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int lineCount ;

extern int yydebug;

extern AST* programa ;


void printAST (int type)
{
	if (type == 283)
		 fprintf(stderr, "AST_CHAR");
	else if (type == 284)
		fprintf(stderr, "AST_INT");
	else if (type == 285)
		fprintf(stderr, "AST_STRING");
	else if (type == 286)
		fprintf(stderr, "AST_BOOL");
	else if (type == 287)
		fprintf(stderr, "AST_TRUE");
	else if (type == 288)
		fprintf(stderr, "AST_FALSE");
	else if (type == 289)
		fprintf(stderr, "AST_NOT");
	else if (type == 290)
		fprintf(stderr, "AST_WHILE");
	else if (type == 291)
		fprintf(stderr, "AST_IF");
	else if (type == 292)
		fprintf(stderr, "AST_ELSE");
	else if (type == 293)
		fprintf(stderr, "AST_END");
	else if (type == 294)
		fprintf(stderr, "AST_NEW");
	else if (type == 295)
		fprintf(stderr, "AST_RET");
	else if (type == 296)
		fprintf(stderr, "AST_FUN");
	else if (type == 297)
		fprintf(stderr, "AST_GREATER");
	else if (type == 298)
		fprintf(stderr, "AST_LESS");
	else if (type == 299)
		fprintf(stderr, "AST_GREATER_EQUAL");
	else if (type == 300)
		fprintf(stderr, "AST_LESS_EQUAL");
	else if (type == 301)
		fprintf(stderr, "AST_EQUAL");
	else if (type == 302)
		fprintf(stderr, "AST_NOT_EQUAL");
	else if (type == 303)
		fprintf(stderr, "AST_PLUS");
	else if (type == 304)
		fprintf(stderr, "AST_MINUS");
	else if (type == 305)
		fprintf(stderr, "AST_TIMES");
	else if (type == 306)
		fprintf(stderr, "AST_DIVIDED");
	else if (type == 307)
		fprintf(stderr, "AST_AND");
	else if (type == 308)
		fprintf(stderr, "AST_OR");
	else if (type == 309)
		fprintf(stderr, "AST_ID");
	else if (type == 310)
		fprintf(stderr, "AST_PROGRAM");
	else if (type == 311)
		fprintf(stderr, "AST_GLOBAL");
	else if (type == 312)
		fprintf(stderr, "AST_BLOCK");
	else if (type == 313)
		fprintf(stderr, "AST_BLOCK_ELSE");
	else if (type == 314)
		fprintf(stderr, "AST_ELSEIF");
	else if (type == 315)
		fprintf(stderr, "AST_PARAM");
	else if (type == 316)
		fprintf(stderr, "AST_ATRIB");
	else if (type == 317)
		fprintf(stderr, "AST_NEG");
	else if (type == 318)
		fprintf(stderr, "AST_CALL");
	else
		fprintf(stderr, "NO AST");
}

void addTab (int numTab)
{
	int cont;
	for(cont=0;cont<numTab;cont++)
	{
		fprintf(stderr, "  ");
	}
}
void prettyPrinter(AST* node)
{	
	int numTab = 0 ;

	while(node != NULL)
	{
		addTab (numTab) ;
		printAST (node->type) ;
		//if(node->stringVal != NULL)
			//fprintf(stderr, " %s\n", node->stringVal);
		fprintf(stderr, " @%d\n", node->line);

		while(node->nextSibling != NULL)
		{	
			node = node->nextSibling ;
			addTab (numTab) ;
			printAST (node->type) ;
			//if(node->stringVal != NULL)
				//fprintf(stderr, " %s\n", node->stringVal);
			fprintf(stderr, " @%d\n", node->line);
			
		}
	
		node = node->firstChild ;
		numTab++ ;
	}
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
	fprintf(stderr, "error!\n");
	yyparse();
	fprintf(stderr, "Nao ha erros de sintaxe\n");
	printf ("Nao ha erros de sintaxe\n");	
	prettyPrinter(programa) ;
}

