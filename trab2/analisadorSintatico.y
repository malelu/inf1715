 /*declarações*/
%{

#include "token.h"

%}

%token TK_CHAR
%token TK_INT
%token TK_STRING
%token TK_BOOL
%token TK_TRUE
%token TK_FALSE
%token TK_NOT  
%token TK_WHILE
%token TK_LOOP 
%token TK_IF 
%token TK_ELSE
%token TK_END 
%token TK_NEW 
%token TK_RET 
%token TK_FUN
%token TK_GREATER_EQUAL
%token TK_LESS_EQUAL
%token TK_NOT_EQUAL
%token TK_AND 
%token TK_OR 
%token TK_NUMINT 
%token TK_ID
%token TK_LITERAL_STRING
%token TK_LINE 
%token ERROR

%%
 /*regras de tradução */
programa: funcao lista_funcao 
	;
lista_funcao : /* vazio */ 
	| funcao lista_funcao
	;
funcao	: TK_FUN TK_ID '(' params ')' ':' tipo nl
          	entradas
          TK_END nl
	| TK_FUN TK_ID '(' params ')' nl
                entradas
          TK_END nl
	;
params	: /*vazio*/ | parametro lista_parametro
	;
lista_parametro : /* vazio */ | lista_parametro ',' parametro
	;
parametro : TK_ID ':' tipo
	;
entradas: TK_ID ':' tipo nl entradas
	| comando nl lista_comando
	| /* vazio */
	;
tipo    : tipobase | '[' ']' tipo
	;
tipobase: TK_INT 
	| TK_CHAR 
	| TK_BOOL 
	| TK_STRING
	;
	/*
	lista_declvar : /* vazio 
	| declvar lista_declvar  
	;
declvar   : TK_ID ':' tipo nl
	;*/
lista_comando : /* vazio */ 
	| comando nl lista_comando
	;
comando	: cmdif 
	| cmdwhile 
	| cmdatrib 
	| cmdreturn 
	| chamada 
	;
cmdif	: TK_IF exp nl
                lista_comando
             	entradas_else
          TK_END
	;
entradas_else : TK_ELSE TK_IF exp nl lista_comando entradas_else
	| TK_ELSE nl lista_comando
	| /* vazio */
	;
/*lista_else_if : /* vazio 
	| TK_ELSE TK_IF exp nl lista_comando lista_else_if
	;
lista_else : /* vazio *
	| TK_ELSE nl lista_comando lista_else
	; */
cmdwhile: TK_WHILE exp nl
                lista_comando
          TK_LOOP
	;
cmdatrib: TK_ID '=' exp
	;
chamada : TK_ID '(' lista_exp ')'
	;
lista_exp  : /* vazio */ 
	| exp sublista_exp
	;
sublista_exp : /* vazio */ 
	| ',' exp sublista_exp
	; 
cmdreturn : TK_RET exp 
	| TK_RET
	;
nl 	: TK_LINE 
	| TK_LINE nl
	;
exp 	: exp_or 
	;
exp_or  : exp_and 
	| exp_or TK_OR exp_and
	;
exp_and : exp_less 
	| exp_and TK_AND exp_less
	;
exp_less :  exp_add 
	| exp_less '<' exp_add 
	| exp_less '>' exp_add 
	| exp_less '=' exp_add
	| exp_less TK_LESS_EQUAL exp_add
	| exp_less TK_GREATER_EQUAL exp_add
	| exp_less TK_NOT_EQUAL exp_add
	;
exp_add : exp_times 
	| exp_add '+' exp_times 	/*{ $$.value = $1.value + $3.value; }*/
	| exp_add '-' exp_times		/*{ $$.value = $1.value - $3.value; }*/
	;
exp_times : exp_un 	
	| exp_times '*' exp_un 		/*{ $$.value = $1.value * $3.value; }*/
	| exp_times '/' exp_un		/*{ $$.value = $1.value / $3.value; }*/
	;
exp_un : TK_NOT exp_un
	| '-' exp_un 
	| exp_fin
	;
exp_fin : TK_NUMINT 
	| TK_LITERAL_STRING
	| TK_TRUE
	| TK_FALSE 
	| TK_NEW '[' exp ']' tipo 
	| TK_ID '(' lista_exp ')'
	| TK_ID 
	| '(' exp ')'			/*{ $$.value = $2.value; }*/
	;     
%%
 /*procedimentos auxiliares */

int yywrap (){ }

