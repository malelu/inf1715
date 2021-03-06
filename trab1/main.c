#include "analisadorLexico.h"
extern int lineCount ;

int main (void)
{
	int token;
	while(token = yylex())
	{
		switch(token)
		{
			case TK_CHAR :
				printf ("line %d => CHAR\n", lineCount);
			break;
			case TK_INT :
				printf ("line %d => INT\n", lineCount);
			break;
			case TK_STRING :
				printf ("line %d => STRING\n", lineCount);
			break;
			case TK_BOOL :
				printf ("line %d => BOOL\n", lineCount);
			break;
			case TK_TRUE :
				printf ("line %d => TRUE\n", lineCount);
			break;
			case TK_FALSE :
				printf ("line %d => FALSE\n", lineCount);
			break;
			case TK_NOT :
				printf ("line %d => NOT\n", lineCount);
			break;
			case TK_WHILE :
				printf ("line %d => WHILE\n", lineCount);
			break;
			case TK_LOOP :
				printf ("line %d => LOOP\n", lineCount);
			break;
			case TK_IF :
				printf ("line %d => IF\n", lineCount);
			break;
			case TK_ELSE :
				printf ("line %d => ELSE\n", lineCount);
			break;
			case TK_END :
				printf ("line %d => END\n", lineCount);
			break;
			case TK_NEW :
				printf ("line %d => NEW\n", lineCount);
			break;
			case TK_RET :
				printf ("line %d => RET\n", lineCount);
			break;
			case TK_FUN :
				printf ("line %d => FUN\n", lineCount);
			break;
			case TK_OPEN_PARENTHESIS :
				printf ("line %d => OPEN_PARENTHESIS\n", lineCount);
			break;
			case TK_CLOSE_PARENTHESIS :
				printf ("line %d => CLOSE_PARENTHESIS\n", lineCount);
			break;
			case TK_COMMA :
				printf ("line %d => COMMA\n", lineCount);
			break;
			case TK_COLLON :
				printf ("line %d => COLLON\n", lineCount);
			break;
			case TK_GREATER :
				printf ("line %d => GREATER\n", lineCount);
			break;
			case TK_LESS :
				printf ("line %d => LESS\n", lineCount);
			break;
			case TK_GREATER_EQUAL :
				printf ("line %d => GREATER_EQUAL\n", lineCount);
			break;
			case TK_LESS_EQUAL :
				printf ("line %d => LESS_EQUAL\n", lineCount);
			break;
			case TK_EQUAL :
				printf ("line %d => EQUAL\n", lineCount);
			break;
			case TK_NOT_EQUAL :
				printf ("line %d => NOT_EQUAL\n", lineCount);
			break;
			case TK_OPEN_BRACKET :
				printf ("line %d => OPEN_BRACKET\n", lineCount);
			break;
			case TK_CLOSE_BRACKET :
				printf ("line %d => CLOSE_BRACKET\n", lineCount);
			break;
			case TK_PLUS :
				printf ("line %d => PLUS\n", lineCount);
			break;
			case TK_MINUS :
				printf ("line %d => MINUS\n", lineCount);
			break;
			case TK_TIMES :
				printf ("line %d => TIMES\n", lineCount);
			break;
			case TK_DIVIDED :
				printf ("line %d => DIVIDED\n", lineCount);
			break;
			case TK_AND :
				printf ("line %d => AND\n", lineCount);
			break;
			case TK_OR :
				printf ("line %d => OR\n", lineCount);
			break;
			case TK_NUMINT :
				printf ("line %d => NUMINT->%d\n", lineCount, val.iValor);
			break;
			case TK_ID :
				printf ("line %d => ID->%s\n", lineCount, val.cValor);
			break;
			case TK_LITERAL_STRING :			
				printf("line %d => LITERAL_STRING->%s\n", lineCount, val.cValor);
			break;
			case ERROR :
				printf ("line %d => ERROR->%s\n", lineCount, val.cValor);
			break;

		}
	}
	return 0;
}
