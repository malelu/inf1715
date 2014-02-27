#include "analisadorLexico.h"

int main (void)
{
	int token;
	while(token = yylex())
	{
		switch(token)
		{
			case TK_CHAR :
				printf ("CHAR\n");
			break;
			case TK_INT :
				printf ("INT\n");
			break;
			case TK_STRING :
				printf ("STRING\n");
			break;
			case TK_BOOL :
				printf ("BOOL\n");
			break;
			case TK_TRUE :
				printf ("TRUE\n");
			break;
			case TK_FALSE :
				printf ("FALSE\n");
			break;
			case TK_NOT :
				printf ("NOT\n");
			break;
			case TK_WHILE :
				printf ("WHILE\n");
			break;
			case TK_LOOP :
				printf ("LOOP\n");
			break;
			case TK_IF :
				printf ("IF\n");
			break;
			case TK_ELSE :
				printf ("ELSE\n");
			break;
			case TK_END :
				printf ("END\n");
			break;
			case TK_NEW :
				printf ("NEW\n");
			break;
			case TK_RET :
				printf ("RET\n");
			break;
			case TK_FUN :
				printf ("FUN\n");
			break;
			case TK_OPEN_PARENTHESIS :
				printf ("OPEN_PARENTHESIS\n");
			break;
			case TK_CLOSE_PARENTHESIS :
				printf ("CLOSE_PARENTHESIS\n");
			break;
			case TK_COMMA :
				printf ("COMMA\n");
			break;
			case TK_COLLON :
				printf ("COLLON\n");
			break;
			case TK_GREATER :
				printf ("GREATER\n");
			break;
			case TK_LESS :
				printf ("LESS\n");
			break;
			case TK_GREATER_EQUAL :
				printf ("GREATER_EQUAL\n");
			break;
			case TK_LESS_EQUAL :
				printf ("LESS_EQUAL\n");
			break;
			case TK_EQUAL :
				printf ("EQUAL\n");
			break;
			case TK_NOT_EQUAL :
				printf ("NOT_EQUAL\n");
			break;
			case TK_OPEN_BRACKET :
				printf ("OPEN_BRACKET\n");
			break;
			case TK_CLOSE_BRACKET :
				printf ("CLOSE_BRACKET\n");
			break;
			case TK_PLUS :
				printf ("PLUS\n");
			break;
			case TK_MINUS :
				printf ("MINUS\n");
			break;
			case TK_TIMES :
				printf ("TIMES\n");
			break;
			case TK_DIVIDED :
				printf ("DIVIDED\n");
			break;
			case TK_AND :
				printf ("AND\n");
			break;
			case TK_OR :
				printf ("OR\n");
			break;
			case TK_NUMINT :
				printf ("NUMINT->%d\n", val.iValor);
			break;
			case TK_ID :
				printf ("ID->%s\n", val.cValor);
			break;
			case TK_LITERAL_STRING :			
				printf("LITERAL_STRING->%s\n", val.cValor);
			break;
			case ERROR :
				printf ("ERROR->%s\n", val.cValor);
			break;

		}
	}
	return 0;
}
