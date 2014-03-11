 /* declaração */
%{
#include <string.h>
#include "y.tab.h"

union Valor{
	char* cValor;
	int iValor;
	double fValor;
}val;

void check (int i, int j, int tam, char* sentence, char* text) ;
char* createString (char* text) ;

int numLinha = 1;
%}
 /* expressoes regulares */
digit [0-9]
exp [eE][-+]?[0-9]+
hexa "0"[xX][0-9 a-fA-F]+
letter [a-zA-Z]
isSpace [ \t\r\v\f]+
line [\n]
numInt {digit}+|{hexa}
fraction ("."{digit}+|{digit}+".")
id (_|{letter})+(_|{letter}|{digit})*
numFloat (({digit}+{fraction}|{fraction})({exp})?|{digit}+{exp}) 
openComment "/*"
comment ("/*"([^*]|\n|"*"+[^*/])*"*"*"*/")
quotMark \"
string {quotMark}(\\.|[^\\"\n])*{quotMark}
other .
 /* regras */
%%

"char" {return TK_CHAR;}
"int" {return TK_INT;}
"float" {return TK_FLOAT;}
"while" {return TK_WHILE;}
"if" {return TK_IF;}
"else" {return TK_ELSE;}
"new" {return TK_NEW;}
"return" {return TK_RET;}
"void" {return TK_VOID;}
">=" {return TK_GE;}
"<=" {return TK_LE;}
"==" {return TK_EE;}
"!=" {return TK_NE;}
"&&" {return TK_AND;}
"||" {return TK_OR;}
{numInt} {
	val.cValor = (char*)malloc(sizeof(strlen(yytext)+1));
	strcpy( val.cValor, yytext) ;
	if(val.cValor[0] != '0') 		/* caso o numero não esteja em hexadecimal */
		val.iValor = atoi(val.cValor); 	
	else	
		val.iValor = (int)strtol(val.cValor, 0, 0);
	return TK_NUMINT;
	}
{numFloat} {
	val.fValor = atof(yytext); 	
	return TK_NUMFLOAT;
	}
{id} {
	val.cValor = (char*)malloc(sizeof(strlen(yytext)+1));
	strcpy( val.cValor, yytext) ; 	
	return TK_ID;
	}
{string} { 
	val.cValor = createString (yytext);
	return TK_STRING;
	}
{comment} { } 
{openComment} {
	printf("erro: COMENTARIO ABERTO");
	exit(1);
}
{quotMark} {
	printf (" ERRO: STRING ABERTA");
	exit(1);
	}
{isSpace} { 
	val.cValor = (char*)malloc(sizeof(strlen(yytext)+1));
	strcpy( val.cValor, yytext) ; 
}
{line} {
	numLinha++;
}
{other} {
	return yytext[0];
} 

%%

void check (int i, int j, int tam, char* sentence, char* text)
{
	char letra ;
 
	letra = text[i+1] ;

	if(letra == 'n')			/*caso encontre um \n*/
		sentence[j] = '\n';	
	else if(letra == 't')			/*caso encontre um \t*/
		sentence[j] = '\t';	
	else if(letra == '\\')			/*caso encontre um \\*/
		sentence[j] = '\\';	
	else if(letra == '"')			/*caso encontre um \"*/
		sentence[j] = '\"';
	else					/* senão a string é inválida */ 
	{
		printf(" STRING INVALIDA-> \\%c", letra);
		exit(1);
	}
}

char* createString (char* text)
{
	int i = 1, j = 0;
	char letra ;
	char* sentence ;
	int len;

	len = strlen(text);			/*guarda o tamanho da string*/

	sentence = (char*)malloc(len*sizeof(char));

	while(i<len-1) 				/*imprime a string sem as aspas*/
	{
		letra = text[i] ;
		
		while(text[i] == '\\') 		/*caso ache uma barra*/
		{
			check (i, j, len, sentence, text);
			i = i+2;
			j++;
		}
			
		if(i<len-1) 			/*caso o i de retorno esteja no limite*/
		{
			sentence[j] = text[i];
			i++;
			j++;
		}
	}
	sentence[j] = '\0' ;

	return sentence ; 

}
