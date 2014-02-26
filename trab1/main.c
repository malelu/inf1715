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
			case TK_FLOAT :
				printf ("FLOAT\n");
			break;
			case TK_WHILE :
				printf ("WHILE\n");
			break;
			case TK_IF :
				printf ("IF\n");
			break;
			case TK_ELSE :
				printf ("ELSE\n");
			break;
			case TK_NEW :
				printf ("NEW\n");
			break;
			case TK_RET :
				printf ("RET\n");
			break;
			case TK_VOID :
				printf ("VOID\n");
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
			case TK_STRING :			
				printf("STRING->%s\n", val.cValor);
			break;
			case TK_SYMBOL :
				printf ("%s\n", val.cValor);
			break;

		}
	}
	return 0;
}
