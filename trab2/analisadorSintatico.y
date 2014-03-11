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
programa  : funcao { funcao }
	;
funcao    -> 'fun' ID '(' [ params ] ')' [ ':' tipo ] NL
                { declvar NL }
                { comando NL }
             'end' NL
	;
params    : /*vazio*/ | parametro { ',' parametro }
	;
parametro : ID ':' tipo
	;
tipo      : tipobase | '[' ']' tipo
	;
tipobase  : 'int' | 'bool' | 'char' | 'string'
	;
declvar   : ID ':' tipo NL
	;
comando   : cmdif | cmdwhile | cmdatrib | cmdreturn | chamada 
	;
cmdif     : 'if' exp NL
                { comando NL }
             { 'else' 'if' exp NL
                { comando NL }
             }
             { 'else' NL
                { comando NL }
             }
             'end'
	;
cmdwhile  : 'while' exp NL
                { comando NL }
             'loop'
	;
cmdatrib  : ID '=' exp
	;
chamada   : ID '(' listaexp ')'
	;
listaexp  : /*vazio*/ | exp { ',' exp }
	;
cmdreturn : 'return' exp | 'return'
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

