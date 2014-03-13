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
lista_parametro : /* vazio */ | lista_parametro ',' parametro
	;
parametro : TK_ID ':' tipo
	;
tipo      : tipobase | '[' ']' tipo
	;
tipobase  : TK_INT | TK_CHAR | TK_BOOL | TK_STRING
	;
lista_declvar : /* vazio */ | declvar lista_declvar  
	;
declvar   : TK_ID ':' tipo TK_LINE
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
cmdatrib  : TK_ID '=' exp
	;
chamada   : TK_ID '(' lista_exp ')'
	;
lista_exp  : /* vazio */ | exp sublista_exp
	;
sublista_exp : /* vazio */ | ',' exp sublista_exp
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
	| exp_less '<' exp_add 
	| exp_less '>' exp_add 
	| exp_less '=' exp_add
	| exp_less TK_LESS_EQUAL exp_add
	| exp_less TK_GREATER_EQUAL exp_add
	;
exp_add : exp_times | exp_add '+' exp_times | exp_add '-' exp_times
	;
exp_times : exp_un | exp_times '*' exp_un | exp_times '/' exp_un
	;
exp_un : TK_NOT exp_un | exp_fin
	;
exp_fin : TK_NUMINT | TK_NEW tipo '[' exp ']' | chamada | '(' exp ')'
	;     
%%
 /*procedimentos auxiliares */

int yywrap (){ }

