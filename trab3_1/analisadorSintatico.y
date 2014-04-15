 /*declarações*/
%{
#include "ast.h"
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
programa: decl lista_decl 			{ $$.node = AST_new(AST_PROGRAM, 1);
						  AST_addChild($$.node, $1.node);
						  AST_addChildren($$.node, $2.node); 
						  AST_prettyPrinter($$.node); }

	| nl decl lista_decl			{ $$.node = AST_new(AST_PROGRAM, 1);
						  AST_addChildren($$.node, $2.node); }
	;
decl	: funcao 				{ $$.node = $1.node; }
	| global				{ $$.node = $1.node; }
	;
global	: TK_ID ':' tipo nl			{ $$.node = AST_new(AST_GLOBAL, $1.line);
 						  AST_addChild($$.node, AST_newStringFromToken($1.cValue));
						  AST_addChild($$.node, $3.node); }
	;
lista_decl : /* vazio */ 			{ $$.node = NULL; }
	| decl lista_decl			{ $$.node = AST_prependSibling($2.node, $1.node); }
	;
funcao	: TK_FUN TK_ID '(' params ')' ':' tipo nl	
		entradas
	  TK_END nl				{ $$.node = AST_new(AST_FUN, $1.line);
					          AST_addChild($$.node, AST_newStringFromToken($2.cValue));
	  					  AST_addChild($$.node, $4.node);
						  AST_addChild($$.node, $7.node);
					  	  AST* block = AST_new(AST_BLOCK, $9.line);
          					  AST_addChildren(block, $9.node);
					  	  AST_addChild($$.node, block); }  
						     

	| TK_FUN TK_ID '(' params ')' nl	
		entradas
	  TK_END nl				{ $$.node = AST_new(AST_FUN, $1.line);
                				  AST_addChild($$.node, AST_newStringFromToken($2.cValue));
          					  AST_addChild($$.node, $4.node);
					 	  AST* block = AST_new(AST_BLOCK, $7.line);
          					  AST_addChildren(block, $7.node);
					  	  AST_addChild($$.node, block); } 
	;
params	: /*vazio*/ 				{ $$.node = NULL; }
	| parametro lista_parametro		{ $$.node = AST_prependSibling($2.node, $1.node); }
	;
lista_parametro : /* vazio */ 			{ $$.node = NULL; }
	| lista_parametro ',' parametro		{ $$.node = AST_prependSibling($3.node, $1.node); }
	;
parametro : TK_ID ':' tipo			{ $$.node = AST_new(AST_PARAM, $1.line);
						  AST_addChild($$.node, AST_newStringFromToken($1.cValue));
						  AST_addChild($$.node, $3.node); }
	;
entradas: TK_ID ':' tipo nl entradas		
	| comando nl lista_comando		{ $$.node = AST_prependSibling($3.node, $1.node); }
	| /* vazio */				{ $$.node = NULL; }
	;
tipo    : tipobase 				{ $$.node = $1.node; }
	| '[' ']' tipo				{ $$.node = $3.node; }
	;
tipobase: TK_INT 				{ $$.node = AST_new(AST_INT, $1.line) ; }
	| TK_CHAR 				{ $$.node = AST_new(AST_CHAR, $1.line) ; }
	| TK_BOOL 				{ $$.node = AST_new(AST_BOOL, $1.line) ; }
	| TK_STRING				{ $$.node = AST_new(AST_STRING, $1.line) ; }
	;
lista_comando : /* vazio */ 			{ $$.node = NULL; }
	| comando nl lista_comando		{ $$.node = AST_prependSibling($3.node, $1.node); }
	;
comando	: cmdif 				{ $$.node = $1.node; }
	| cmdwhile 				{ $$.node = $1.node; }
	| cmdatrib 				{ $$.node = $1.node; }
	| cmdreturn 				{ $$.node = $1.node; }
	| chamada 				{ $$.node = $1.node; }
	;
cmdif	: TK_IF exp nl				
		entradas
		entradas_else
	  TK_END				{ $$.node = AST_new(AST_IF, $1.line);			
               					  AST_addChild($$.node, $2.node);
             					  AST* block = AST_new(AST_BLOCK, $4.line);
          					  AST_addChildren(block, $4.node);
					  	  AST_addChild($$.node, block);
						  AST* block_else = AST_new(AST_BLOCK_ELSE, $5.line);
						  AST_addChildren(block, $5.node);
					  	  AST_addChild($$.node, block_else); }
	;
entradas_else : TK_ELSE TK_IF exp nl entradas entradas_else
						{ $$.node = AST_new(AST_ELSEIF, $1.line);
						  AST_addChild($$.node, $3.node);
						  AST* block = AST_new(AST_BLOCK, $5.line);
						  AST_addChildren(block, $5.node);
					  	  AST_addChild($$.node, block);
						  AST* block_else = AST_new(AST_BLOCK_ELSE, $6.line);
						  AST_addChildren(block, $6.node);
					  	  AST_addChild($$.node, block_else); }

	| TK_ELSE nl entradas			{ $$.node = AST_new(AST_ELSE, $1.line);
						  AST* block = AST_new(AST_BLOCK, $3.line);
						  AST_addChildren(block, $3.node);
					  	  AST_addChild($$.node, block); }

	| /* vazio */				{ $$.node = NULL; }
	;
cmdwhile: TK_WHILE exp nl			
		entradas
	  TK_LOOP				{ $$.node = AST_new(AST_WHILE, $1.line);
                				  AST_addChild($$.node, $2.node);
          					  AST* block = AST_new(AST_BLOCK, $4.line);
						  AST_addChildren(block, $4.node);
					  	  AST_addChild($$.node, block); }
	;
cmdatrib: var '=' exp				{ $$.node = AST_new(AST_ATRIB, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
	;
var	: TK_ID 				{ $$.node = AST_newStringFromToken($1.cValue); }
	| var '[' exp ']'			{ $$.node = AST_prependSibling($3.node, $1.node); }
	;
chamada : TK_ID '(' lista_exp ')'		{ $$.node = AST_new(AST_CALL, $1.line);
						  AST_addChild($$.node, AST_newStringFromToken($1.cValue));
						  AST_addChild($$.node, $3.node); }	
	;
lista_exp  : /* vazio */ 			{ $$.node = NULL; }
	| exp sublista_exp			{ $$.node = AST_prependSibling($2.node, $1.node); }
	;
sublista_exp : /* vazio */ 			{ $$.node = NULL; }
	| ',' exp sublista_exp
	; 
cmdreturn : TK_RET exp 				{ $$.node = AST_new(AST_RET, $1.line);
						  AST_addChild($$.node, $2.node); }
	| TK_RET				{ $$.node = AST_new(AST_RET, $1.line); }
	;
nl 	: TK_LINE 				{}
	| TK_LINE nl				{}
	;
exp 	: exp_or 				{ $$.node = $1.node; }
	;
exp_or  : exp_and 				{ $$.node = $1.node; }
	| exp_or TK_OR exp_and			{ $$.node = AST_new(AST_OR, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
	;
exp_and : exp_less 				{ $$.node = $1.node; }
	| exp_and TK_AND exp_less		{ $$.node = AST_new(AST_AND, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
	;
exp_less :  exp_add 				{ $$.node = $1.node; }
	| exp_less '<' exp_add 			{ $$.node = AST_new(AST_LESS, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_less '>' exp_add 			{ $$.node = AST_new(AST_GREATER, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_less '=' exp_add			{ $$.node = AST_new(AST_EQUAL, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_less TK_LESS_EQUAL exp_add	{ $$.node = AST_new(AST_LESS_EQUAL, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_less TK_GREATER_EQUAL exp_add	{ $$.node = AST_new(AST_GREATER_EQUAL, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_less TK_NOT_EQUAL exp_add		{ $$.node = AST_new(AST_NOT_EQUAL, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
	;
exp_add : exp_times 				{ $$.node = $1.node; }
	| exp_add '+' exp_times 		{ $$.node = AST_new(AST_PLUS, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
						
	| exp_add '-' exp_times			{ $$.node = AST_new(AST_MINUS, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }	
	;
exp_times : exp_un 				{ $$.node = $1.node; }
	| exp_times '*' exp_un 			{ $$.node = AST_new(AST_TIMES, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }

	| exp_times '/' exp_un			{ $$.node = AST_new(AST_DIVIDED, $1.line);
						  AST_addChild($$.node, $1.node);
						  AST_addChild($$.node, $3.node); }
	;
exp_un : TK_NOT exp_un				{ $$.node = AST_new(AST_NOT, $1.line);
						  AST_addChild($$.node, $2.node); }

	| '-' exp_un 				{ $$.node = AST_new(AST_NEG, $1.line);
						  AST_addChild($$.node, $2.node); }

	| exp_fin				{ $$.node = $1.node; }
	;
exp_fin : TK_NUMINT				{ $$.node = newNumFromToken($1.iValue); }
	| TK_LITERAL_STRING			{ $$.node = AST_newStringFromToken($1.cValue); }
	| TK_TRUE				{ $$.node = AST_new(AST_TRUE, $1.line) ; }
	| TK_FALSE 				{ $$.node = AST_new(AST_FALSE, $1.line) ; }
	| TK_NEW '[' exp ']' tipo 		{ $$.node = AST_new(AST_NEW, $1.line);
						  AST_addChild($$.node, $3.node);
						  AST_addChild($$.node, $5.node); }

	| TK_ID '(' lista_exp ')'		{ $$.node = AST_new(AST_CALL, $1.line);
						  AST_addChild($$.node, AST_newStringFromToken($1.cValue));
						  AST_addChild($$.node, $3.node); }
	| var 					{ $$.node = $1.node; }
	| '(' exp ')'				{ $$.node = $2.node; }	
	;     
%%
 /*procedimentos auxiliares */

int yywrap (){ }

