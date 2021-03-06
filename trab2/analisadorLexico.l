
 /* declaração */
%{
#include <string.h>
#include "token.h"
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
comment ("/*"([^*]|\n|"*"+[^*/])*"*"*"*/")|("//"[^\n]*)
quotMark \"
string {quotMark}(\\.|[^\\"\n])*{quotMark}

%%
%line
 /* regras */
"char" {yylval.line = lineCount; return TK_CHAR;}

"int" {yylval.line = lineCount; return TK_INT;}

"string" {yylval.line = lineCount; return TK_STRING;}

"bool" {yylval.line = lineCount; return TK_BOOL;}

"true" {yylval.line = lineCount; return TK_TRUE;}

"false" {yylval.line = lineCount; return TK_FALSE;}

"not" {yylval.line = lineCount; return TK_NOT;}

"while" {yylval.line = lineCount; return TK_WHILE;}

"loop" {yylval.line = lineCount; return TK_LOOP;}

"if" {yylval.line = lineCount; return TK_IF;}

"else" {yylval.line = lineCount; return TK_ELSE;}

"end" {yylval.line = lineCount; return TK_END;}

"new" {yylval.line = lineCount; return TK_NEW;}

"return" {yylval.line = lineCount; return TK_RET;}

"fun" {yylval.line = lineCount; return TK_FUN;}

"(" {yylval.line = lineCount; return '(';}

")" {yylval.line = lineCount; return ')';}

"," {yylval.line = lineCount; return ',';}

":" {yylval.line = lineCount; return ':';}

">" {yylval.line = lineCount; return '>';}

"<" {yylval.line = lineCount; return '<';}

">=" {yylval.line = lineCount; return TK_GREATER_EQUAL;}

"<=" {yylval.line = lineCount; return TK_LESS_EQUAL;}

"=" {yylval.line = lineCount; return '=';}

"<>" {yylval.line = lineCount; return TK_NOT_EQUAL;}

"[" {yylval.line = lineCount; return '[';}

"]" {yylval.line = lineCount; return ']';}

"+" {yylval.line = lineCount; return '+';}

"-" {yylval.line = lineCount; return '-';}

"*" {yylval.line = lineCount; return '*';}

"/" {yylval.line = lineCount; return '/';}

"and" {yylval.line = lineCount; return TK_AND;}

"or" {yylval.line = lineCount; return TK_OR;}

{numInt} {
	yylval.cValue = yytext ;
	if(yylval.cValue[0] != '0') 		/* caso o numero não esteja em hexadecimal */
		yylval.iValue = atoi(yylval.cValue); 	
	else	
		yylval.iValue = (int)strtol(yylval.cValue, 0, 0);

	yylval.line = lineCount;
	return TK_NUMINT;
	}

{id} {
	yylval.cValue = yytext;
	yylval.line = lineCount; 	
	return TK_ID;
	}

{string} { 
	yylval.cValue = createString (yytext);
	yylval.line = lineCount;
	return TK_LITERAL_STRING;
	}

{comment} { } 

{openComment} {
	printf("line %d => ERROR: OPEN COMMENT\n", lineCount);
	exit(1);
}

{quotMark} {
	printf ("line: %d => ERROR: OPEN STRING\n", lineCount);
	exit(1);
	}

{line} {
	yylval.line = lineCount ;
	lineCount++;
	return TK_LINE;
}

{isSpace} { }
. {
	yylval.cValue = yytext;
	yylval.line = lineCount;
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
