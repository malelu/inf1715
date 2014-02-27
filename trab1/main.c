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
			case TK_GE :
				printf ("GE\n");
			break;
			case TK_LE :
				printf ("LE\n");
			break;
			case TK_EE :
				printf ("EE\n");
			break;
			case TK_NE :
				printf ("NE\n");
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
			case TK_NUMFLOAT :
				printf ("NUMFLOAT->%f\n", val.fValor);
			break;
			case TK_ID :
				printf ("ID->%s\n", val.cValor);
			break;
			case TK_LITERAL_STRING :			
				printf("STRING->%s\n", val.cValor);
			break;
			case OTHER :
				printf ("%s\n", val.cValor);
			break;

		}
	}
	return 0;
}
