 /*declarações*/
%{
%}

%token TK_CHAR
%token TK_INT
%token TK_FLOAT
%token TK_WHILE
%token TK_IF  
%token TK_ELSE
%token TK_NEW
%token TK_RET
%token TK_VOID
%token TK_GE
%token TK_LE
%token TK_EE
%token TK_NE
%token TK_AND
%token TK_OR
%token TK_NUMINT
%token TK_NUMFLOAT
%token TK_ID
%token TK_STRING
%nonassoc TK_EMPTY_ELSE
%nonassoc TK_ELSE


%%
 /*regras de tradução */
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

