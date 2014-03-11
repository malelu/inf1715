#include <stdio.h>
#include <stdlib.h>

extern int numLinha ;

extern int yydebug;

void yyerror (const char * s)
{	
	printf("parser error %s \n",s);
	printf("Erro de sintaxe na linha %d\n", numLinha);
	exit(1);
}

int main (void)
{
	//yydebug = 1;
	yyparse();
	printf ("Nao ha erros de sintaxe\n");	
}
