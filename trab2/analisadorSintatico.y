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
%token ERROR
%nonassoc TK_EMPTY_ELSE
%nonassoc TK_ELSE


%%
 /*regras de tradução */
programa  : funcao lista_funcao 
	;
lista_funcao : /* vazio */ | funcao lista_funcao
	;
funcao    -> TK_FUN TK_ID TK_OPEN_PARENTHESIS [ params ] TK_CLOSE_PARENTHESIS [ ':' tipo ] NL
                lista_declvar
                lista_comando
             TK_END NL
	;
params    : /*vazio*/ | parametro { TK_COMMA parametro }
	;
parametro : TK_ID TK_COLLON tipo
	;
tipo      : tipobase | '[' ']' tipo
	;
tipobase  : TK_INT | TK_CHAR | TK_BOOL | TK_STRING
	;
lista_declvar /* vazio */ | declvar lista_declvar
	;
declvar   : TK_ID TK_COLLON tipo NL
	;
lista_comando : /* vazio */ | comando lista_comando
	;
comando   : cmdif | cmdwhile | cmdatrib | cmdreturn | chamada 
	;
cmdif     : TK_IF exp NL
                { comando NL }
             { TK_ELSE TK_IF exp NL
                { comando NL }
             }
             { TK_ELSE NL
                { comando NL }
             }
             TK_END
	;
cmdwhile  : TK_WHILE exp NL
                { comando NL }
             TK_LOOP
	;
cmdatrib  : TK_ID TK_EQUAL exp
	;
chamada   : TK_ID TK_OPEN_PARENTHESIS listaexp TK_CLOSE_PARENTHESIS
	;
listaexp  : /*vazio*/ | exp { TK_COMMA exp }
	;
cmdreturn : TK_RETURN exp | TK_RETURN
	;
exp       : LITNUMERAL
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
	;
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
exp_fin : var | TK_NUMINT | TK_NEW tipo '['exp']' | chamada | TK_OPEN_PARENTHESIS exp TK_CLOSE_PARENTHESIS
	;
 /*anterior*/

programa : lista_declaracao
	;
lista_declaracao : /* empty */| declaracao lista_declaracao
	;	
declaracao : dec_variavel| dec_funcao
	;
dec_variavel : tipo lista_nomes ';'
	;	
lista_nomes : TK_ID | TK_ID ',' lista_nomes        
	;
tipo : tipo_base | tipo '[' ']'
	;
tipo_id : tipo TK_ID | TK_VOID TK_ID
	;
tipo_base : TK_INT | TK_CHAR | TK_FLOAT 
	;
dec_funcao : tipo_id '(' parametros ')' bloco
	;
parametros : /* empty */ | parametro | parametro ',' parametros        
	;
parametro : tipo TK_ID
	;
bloco : '{' lista_dec_variavel lista_comando '}' 
	| '{'/* empty */'}' 
	| '{' lista_dec_variavel '}' 
	| '{' lista_comando '}'	
	;
lista_dec_variavel : dec_variavel | lista_dec_variavel dec_variavel 
	;
lista_comando : comando | lista_comando comando 
	; 
comando : TK_IF '(' exp ')' comando parte_else
        | TK_WHILE '(' exp ')' comando
        | TK_ID '=' exp ';'
        | TK_RET exp ';'
	| TK_RET ';'
        | chamada ';'
	| bloco
	;

parte_else : /* empty */ %prec TK_EMPTY_ELSE | TK_ELSE comando
	;
var : TK_ID | exp_fin '[' exp ']'
	;
exp : exp_or 
	;
exp_or : exp_and | exp_or TK_OR exp_and
	;
exp_and : exp_less | exp_and TK_AND exp_less
	;
exp_less :  exp_add 
	| exp_less '<' exp_add 
	| exp_less '>' exp_add 
	| exp_less TK_EE exp_add
	| exp_less TK_LE exp_add
	| exp_less TK_GE exp_add
	;
exp_add : exp_times | exp_add '+' exp_times | exp_add '-' exp_times
	;
exp_times : exp_un | exp_times '*' exp_un | exp_times '/' exp_un
	;
exp_un : '-'exp_un | '!'exp_un |  exp_fin
	;
exp_fin : var | TK_NUMINT | TK_NUMFLOAT | TK_NEW tipo '['exp']' | chamada | '('exp')'
	;
chamada : TK_ID '(' lista_exp ')'
	;
lista_exp : /* empty */ | exp | exp ',' lista_exp       
%%
 /*procedimentos auxiliares */

int yywrap (){ }

