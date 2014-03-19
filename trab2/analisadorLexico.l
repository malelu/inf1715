
 /* declaração */
%{
#include <string.h>
#include "y.tab.h"

union Valor{
	char* cValor;
	int iValor;
}val;

int lineCount = 1;
void check (int i, int j, int tam, char* sentence, char* text) ;
char* createString (char* text) ;
%}

 /* expressoes regulares */
digit [0-9]
hexa "0"[xX][0-9 a-fA-F]+
letter [a-zA-Z]
isSpace [ \t\r\v\f]+
line [\n]
numInt {digit}+|{hexa}
id (_|{letter})+(_|{letter}|{digit})*
openComment "/*"
comment ("/*"([^*]|\n|"*"+[^*/])*"*"*"*/")
quotMark \"
string {quotMark}(\\.|[^\\"\n])*{quotMark}

%%
%line
 /* regras */
"char" {return TK_CHAR;}
"int" {return TK_INT;}
"string" {return TK_STRING;}
"bool" {return TK_BOOL;}
"true" {return TK_TRUE;}
"false" {return TK_FALSE;}
"not" {return TK_NOT;}
"while" {return TK_WHILE;}
"loop" {return TK_LOOP;}
"if" {return TK_IF;}
"else" {return TK_ELSE;}
"end" {return TK_END;}
"new" {return TK_NEW;}
"return" {return TK_RET;}
"fun" {return TK_FUN;}
"(" {return '(';}
")" {return ')';}
"," {return ',';}
":" {return ':';}
">" {return '>';}
"<" {return '<';}
">=" {return TK_GREATER_EQUAL;}
"<=" {return TK_LESS_EQUAL;}
"=" {return '=';}
"<>" {return TK_NOT_EQUAL;}
"[" {return '[';}
"]" {return ']';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"and" {return TK_AND;}
"or" {return TK_OR;}
{numInt} {
	val.cValor = yytext ;
	if(val.cValor[0] != '0') 		/* caso o numero não esteja em hexadecimal */
		val.iValor = atoi(val.cValor); 	
	else	
		val.iValor = (int)strtol(val.cValor, 0, 0);
	return TK_NUMINT;
	}
{id} {
	val.cValor = yytext; 	
	return TK_ID;
	}
{string} { 
	val.cValor = createString (yytext);
	return TK_LITERAL_STRING;
	}
{comment} { } 
{openComment} {
	printf("line %d => ERROR: OPEN COMMENT", lineCount);
	exit(1);
}
{quotMark} {
	printf ("line: %d => ERROR: OPEN STRING", lineCount);
	exit(1);
	}
{line} {
	lineCount++;
	return TK_LINE;
}
{isSpace} { }
. {
	val.cValor = yytext;
	return ERROR;
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
		printf("line %d => INVALID STRING-> \\%c", lineCount, letra);
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
