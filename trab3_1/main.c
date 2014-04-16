#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int lineCount ;

extern int yydebug;

extern AST* programa ;


void printAST (int type)
{
	if (type == 283)
		 fprintf(stderr, "AST_CHAR\n");
	else if (type == 284)
		fprintf(stderr, "AST_INT\n");
	else if (type == 285)
		fprintf(stderr, "AST_STRING\n");
	else if (type == 286)
		fprintf(stderr, "AST_BOOL\n");
	else if (type == 287)
		fprintf(stderr, "AST_TRUE\n");
	else if (type == 288)
		fprintf(stderr, "AST_FALSE\n");
	else if (type == 289)
		fprintf(stderr, "AST_NOT\n");
	else if (type == 290)
		fprintf(stderr, "AST_WHILE\n");
	else if (type == 291)
		fprintf(stderr, "AST_IF\n");
	else if (type == 292)
		fprintf(stderr, "AST_ELSE\n");
	else if (type == 293)
		fprintf(stderr, "AST_END\n");
	else if (type == 294)
		fprintf(stderr, "AST_NEW\n");
	else if (type == 295)
		fprintf(stderr, "AST_RET\n");
	else if (type == 296)
		fprintf(stderr, "AST_FUN\n");
	else if (type == 297)
		fprintf(stderr, "AST_GREATER\n");
	else if (type == 298)
		fprintf(stderr, "AST_LESS\n");
	else if (type == 299)
		fprintf(stderr, "AST_GREATER_EQUAL\n");
	else if (type == 300)
		fprintf(stderr, "AST_LESS_EQUAL\n");
	else if (type == 301)
		fprintf(stderr, "AST_EQUAL\n");
	else if (type == 302)
		fprintf(stderr, "AST_NOT_EQUAL\n");
	else if (type == 303)
		fprintf(stderr, "AST_PLUS\n");
	else if (type == 304)
		fprintf(stderr, "AST_MINUS\n");
	else if (type == 305)
		fprintf(stderr, "AST_TIMES\n");
	else if (type == 306)
		fprintf(stderr, "AST_DIVIDED\n");
	else if (type == 307)
		fprintf(stderr, "AST_AND\n");
	else if (type == 308)
		fprintf(stderr, "AST_OR\n");
	else if (type == 309)
		fprintf(stderr, "AST_ID\n");
	else if (type == 310)
		fprintf(stderr, "AST_PROGRAM\n");
	else if (type == 311)
		fprintf(stderr, "AST_GLOBAL\n");
	else if (type == 312)
		fprintf(stderr, "AST_BLOCK\n");
	else if (type == 313)
		fprintf(stderr, "AST_BLOCK_ELSE\n");
	else if (type == 314)
		fprintf(stderr, "AST_ELSEIF\n");
	else if (type == 315)
		fprintf(stderr, "AST_PARAM\n");
	else if (type == 316)
		fprintf(stderr, "AST_ATRIB\n");
	else if (type == 317)
		fprintf(stderr, "AST_NEG\n");
	else if (type == 318)
		fprintf(stderr, "AST_CALL\n");
}
void prettyPrinter(AST* node)
{
	fprintf(stderr, "pretty\n");
	fprintf(stderr, "%d\n", node->line);
	printAST (node->type) ;
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

