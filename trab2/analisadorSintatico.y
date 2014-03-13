 /*declarações*/
%{
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
%token TK_OPEN_PARENTHESIS
%token TK_CLOSE_PARENTHESIS
%token TK_COMMA
%token TK_COLLON
%token TK_GREATER
%token TK_LESS 
%token TK_GREATER_EQUAL
%token TK_LESS_EQUAL
%token TK_EQUAL
%token TK_NOT_EQUAL
%token TK_OPEN_BRACKET
%token TK_CLOSE_BRACKET
%token TK_PLUS
%token TK_MINUS
%token TK_TIMES
%token TK_DIVIDED 
%token TK_AND 
%token TK_OR 
%token TK_NUMINT 
%token TK_ID
%token TK_LITERAL_STRING
%token TK_LINE 
%token ERROR

%%
 /*regras de tradução */
programa  : funcao lista_funcao 
	;
lista_funcao : /* vazio */ | funcao lista_funcao
	;
funcao	: TK_FUN TK_ID '(' params ')' ':' tipo TK_LINE
                lista_declvar
                lista_comando
             TK_END TK_LINE
	| TK_FUN TK_ID '(' params ')' TK_LINE
                lista_declvar
                lista_comando
             TK_END TK_LINE
	;
params    : /*vazio*/ | parametro lista_parametro
	;
lista_parametro : /* vazio */ | lista_parametro TK_COMMA parametro
	;
parametro : TK_ID TK_COLLON tipo
	;
tipo      : tipobase | TK_OPEN_BRACKET TK_CLOSE_BRACKET tipo
	;
tipobase  : TK_INT | TK_CHAR | TK_BOOL | TK_STRING
	;
lista_declvar : /* vazio */ | declvar lista_declvar  
	;
declvar   : TK_ID TK_COLLON tipo TK_LINE
	;
lista_comando : /* vazio */ | comando TK_LINE lista_comando
	;
comando   : cmdif | cmdwhile | cmdatrib | cmdreturn | chamada 
	;
cmdif     : TK_IF exp TK_LINE
                lista_comando
             lista_else_if
             lista_else
             TK_END
	;
lista_else_if : /* vazio */ | TK_ELSE TK_IF exp TK_LINE lista_comando lista_else_if
	;
lista_else : /* vazio */ | TK_ELSE TK_LINE lista_comando lista_else
	;
cmdwhile  : TK_WHILE exp TK_LINE
                lista_comando
             TK_LOOP
	;
cmdatrib  : TK_ID TK_EQUAL exp
	;
chamada   : TK_ID TK_OPEN_PARENTHESIS lista_exp TK_CLOSE_PARENTHESIS
	;
lista_exp  : /* vazio */ | exp sublista_exp
	;
sublista_exp : /* vazio */ | TK_COMMA exp sublista_exp
	; 
cmdreturn : TK_RET exp | TK_RET
	;
 /*exp       : LITNUMERAL
           | LITSTRING
           | 'new' '[' exp ']' tipo
           | '(' exp ')'
           | chamada
           | exp '+' exp
           | exp '-' exp
           | exp '*' exp
           | exp '/' exp
           | exp '>' exp
           | exp '<' exp
           | exp '>=' exp
           | exp '<=' exp
           | exp '=' exp
           | exp '<>' exp
           | exp 'and' exp
           | exp 'or' exp
           | 'not' exp
	; */
exp : exp_or 
	;
exp_or : exp_and | exp_or TK_OR exp_and
	;
exp_and : exp_less | exp_and TK_AND exp_less
	;
exp_less :  exp_add 
	| exp_less TK_LESS exp_add 
	| exp_less TK_GREATER exp_add 
	| exp_less TK_EQUAL exp_add
	| exp_less TK_LESS_EQUAL exp_add
	| exp_less TK_GREATER_EQUAL exp_add
	;
exp_add : exp_times | exp_add TK_PLUS exp_times | exp_add TK_MINUS exp_times
	;
exp_times : exp_un | exp_times TK_TIMES exp_un | exp_times TK_DIVIDED exp_un
	;
exp_un : TK_NOT exp_un | exp_fin
	;
exp_fin : TK_NUMINT | TK_NEW tipo TK_OPEN_BRACKET exp TK_CLOSE_BRACKET | chamada | TK_OPEN_PARENTHESIS exp TK_CLOSE_PARENTHESIS
	;     
%%
 /*procedimentos auxiliares */

int yywrap (){ }

