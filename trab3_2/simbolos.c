#include "tabela_simbolos.h"
#include "simbolos.h"
#include "ast.h"
#include <stdio.h>
#include <assert.h>

static bool fail(const char* msg, const char* name, AST* node);
static int* Symbols_setExpression (int* ret_expression, AST* exp, int SymbolType, int ASTtype, int size);
static int* Symbols_visitExpression(SymbolTable* st, AST* exp);
static bool Symbols_visitConditional(SymbolTable* st, AST* node);
static bool Symbols_visitIf(SymbolTable* st, AST* _if); 
static bool Symbols_visitElseIf(SymbolTable* st, AST* else_if); 
static bool Symbols_visitElse(SymbolTable* st, AST* _else); 
static bool Symbols_visitWhile(SymbolTable* st, AST* _while);
static bool Symbols_visitReturn(SymbolTable* st, AST* _return);
static bool Symbols_visitNew(SymbolTable* st, AST* _new);
static bool Symbols_visitCall(SymbolTable* st, AST* call);
static bool Symbols_visitAssign(SymbolTable* st, AST* assign);
static bool Symbols_visitDeclVar(SymbolTable* st, AST* declvar);
static void Symbols_setParamGlob(SymbolTable* st, AST* parent, AST* child1, AST* child2, int symbol_type); 
static bool Symbols_getParamGlob(SymbolTable* st, AST* node);
static bool Symbols_visitParameter(SymbolTable* st, AST* parameter); 
static bool Symbols_visitGlobal(SymbolTable* st, AST* global); 
static bool Symbols_visitBlockElse(SymbolTable* st, AST* block_else);
static bool Symbols_visitBlock(SymbolTable* st, AST* block);
static bool Symbols_visitFunction(SymbolTable* st, AST* function); 

static int symbol_table_scope;

static bool fail(const char* msg, const char* name, AST* node) 
{
   	fprintf(stderr, "%s - %s at line %d\n", msg, name, node->line);
   	return false;
}


static int* Symbols_setExpression (int* ret_expression, AST* exp, int SymbolType, int ASTtype, int size)
{
	exp->symbol_type = SymbolType ;
	exp->size = size ;
	ret_expression[0] = ASTtype ;
	ret_expression[1] = size ;
	return ret_expression ;
}

static int* Symbols_visitExpression(SymbolTable* st, AST* exp) 
{
	fprintf(stderr, "entrou no visit expression\n") ;
	int* ret_expression = (int*)malloc(2*sizeof(int)) ;   /* pos[0] = tipo ; pos[1] = tamanho do array */
	int* child1 = (int*)malloc(2*sizeof(int)) ;
	int* child2 = (int*)malloc(2*sizeof(int)) ;
	const char* name = exp->stringVal;

	if (exp->type == AST_NUMINT)
	{
		fprintf(stderr, "visit exp numint\n") ;
		return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, exp->size);
	}
	else if (exp->type == AST_LITERAL_STRING)
	{
		fprintf(stderr, "visit exp lit_string\n") ;
		return Symbols_setExpression (ret_expression, exp, SYM_CHAR, AST_CHAR, exp->size);
	}
	else if (exp->type == AST_TRUE || exp->type == AST_FALSE)
	{
		fprintf(stderr, "visit exp true false\n") ;
		return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, exp->size);
	}
	else if (exp->type == AST_NEW)
	{
		fprintf(stderr, "visit exp new\n") ;
		//TRATAR NEW!!!!!!!!!!!
		Symbols_visitNew(st, exp) ; 
	}
	else if (exp->type == AST_ID)
	{
		fprintf(stderr, "visit exp id\n") ;
		Symbol* existing = SymbolTable_get(st, name);

		if(existing)
		{
			if (existing->type == SYM_INT)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, existing->size);
			}
			else if (existing->type == SYM_BOOL)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, existing->size);
			}
			else if (existing->type == SYM_CHAR )
			{
				return Symbols_setExpression (ret_expression, exp, SYM_CHAR, AST_CHAR, existing->size);
			}
		}

		fprintf(stderr, "undeclared variable! - %s at line %d\n", name, exp->line);
		ret_expression[0]=-1 ;
		ret_expression[1]=-1 ;
		return ret_expression ;

	}

	else if (exp->type == AST_PLUS || exp->type == AST_MINUS || exp->type == AST_TIMES || exp->type == AST_DIVIDED)
	{
		fprintf(stderr, "visit exp contas\n") ;
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if(((child1[0] == AST_NUMINT) || (child1[0] == AST_CHAR)) && ((child2[0] == AST_NUMINT) || (child2[0] = AST_CHAR)))
		{
			if(child1[1] == child2[1] == 0)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, child1[1]);
			}
			else
			{
				fprintf(stderr, "invalid expression! Invalid type sizes! - %s at line %d\n", "+ - * /", exp->line);
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				return ret_expression ;
			}
		}
		else
		{
			fprintf(stderr, "invalid expression! Invalid types! - %s at line %d\n", "+ - * /", exp->line);
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			return ret_expression ;
		}
	}

	else if (exp->type == AST_GREATER || exp->type == AST_LESS || exp->type == AST_GREATER_EQUAL 
		 || exp->type == AST_LESS_EQUAL || exp->type == AST_EQUAL || exp->type == AST_NOT_EQUAL)
	{
		fprintf(stderr, "visit exp > < = etc\n") ;
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if(((child1[0] == AST_NUMINT) || (child1[0] == AST_CHAR)) && ((child2[0] == AST_NUMINT) || (child2[0] = AST_CHAR)))
		{
			if(child1[1] == child2[1] == 0)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0);
			}
			else
			{
				fprintf(stderr, "invalid comparison expression! Invalid type sizes! - %s at line %d\n", "comparison", exp->line);
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				return ret_expression ;
			}
		}
		else
		{
			fprintf(stderr, "invalid comparison expression! - %s at line %d\n", "comparison", exp->line);
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			return ret_expression ;
		}
	}

	else if (exp->type == AST_AND || exp->type == AST_OR)
	{
		fprintf(stderr, "visit exp and/or\n") ;
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if(child1[0] == AST_BOOL && child2[0] == AST_BOOL)
		{
			if(child1[1] == child2[1] == 0)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0);
			}
			else
			{
				fprintf(stderr, "invalid and/or expression! Invalid type sizes! - %s at line %d\n", "and/or", exp->line);
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				return ret_expression ;
			}
		}

		else
		{
			fprintf(stderr, "invalid and/or expression! - %s at line %d\n", "and/or", exp->line);
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			return ret_expression ;
		}
	}

	else if (exp->type == AST_NOT)
	{
		fprintf(stderr, "visit exp not\n") ;
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(child1[0] == AST_BOOL && child1[1] == 0)
		{
			return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0);
		}

		else
		{
			fprintf(stderr, "invalid \"not\" expression! - %s at line %d\n", "not", exp->line);
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			return ret_expression ;
		}
	}

	else if (exp->type == AST_NEG)
	{
		fprintf(stderr, "visit exp neg\n") ;
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(((child1[0] == AST_NUMINT) && (child1[1] == 0)) || ((child1[0] == AST_CHAR) && (child1[1] == 0)))
		{
			return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, 0);
		}

		else
		{
			fprintf(stderr, "invalid - expression! - %s at line %d\n", "neg", exp->line);
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			return ret_expression ;
		}
	}

	fprintf(stderr, "invalid expression! - %s at line %d\n", "exp", exp->line);
	ret_expression[0]=-1 ;
	ret_expression[1]=-1 ;
	return ret_expression ;
}

static bool Symbols_visitConditional(SymbolTable* st, AST* node) 
{
	fprintf(stderr, "entrou no conditional\n") ;
	int* exp_type = (int*)malloc(2*sizeof(int)) ;

	exp_type  = Symbols_visitExpression(st, node->firstChild) ;
	fprintf(stderr, "saiu do visit expression\n") ;

	AST* child = node->firstChild->nextSibling;

	if (exp_type[0] != AST_BOOL)
		return fail("condition expression is not a boolean value!\n", "?!?!", node);
	else if (exp_type[1] != 0)
		return fail("condition expression is a boolean array!\n", "?!?!", node);

	node->symbol_type == SYM_BOOL ;
	node->size = exp_type[1] ;

	while(child != NULL)
	{
		bool ok ;
		if (child->type == AST_BLOCK)
		{
			fprintf(stderr, "entrou visitIf block\n") ;
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_BLOCK_ELSE)
		{
			fprintf(stderr, "entrou visitIf block\n") ;
			ok = Symbols_visitBlockElse(st, child);
		}
		else
			ok = fail("Internal compiler error! - conditional\n", "!?!?", node);

		child = child->nextSibling ;
	
		if(!ok)
			return false ;
	}

	fprintf(stderr, "saiu do conditional\n") ;
	return true ;
}

static bool Symbols_visitIf(SymbolTable* st, AST* _if) 
{
	return Symbols_visitConditional(st, _if) ;
}

static bool Symbols_visitElseIf(SymbolTable* st, AST* else_if) 
{
	return Symbols_visitConditional(st, else_if) ;
}


static bool Symbols_visitElse(SymbolTable* st, AST* _else) 
{
	AST* child = _else->firstChild ;

	while(child != NULL)
	{
		bool ok ;
		if (child->type == AST_BLOCK)
		{
			fprintf(stderr, "entrou visitelse block\n") ;
			ok = Symbols_visitBlock(st, child);
		}
		else
			ok = fail("Internal compiler error! - else\n", "!?!?", _else);

		child = child->nextSibling ;

		if(!ok)
			return false ;
	}

	return true ;
}

static bool Symbols_visitWhile(SymbolTable* st, AST* _while) 
{
	int* exp_type = (int*)malloc(2*sizeof(int)) ;

	exp_type  = Symbols_visitExpression(st, _while->firstChild) ;

	AST* child = _while->firstChild->nextSibling;

	if (exp_type[0] != AST_BOOL)
		return fail("while expression is not a boolean value!\n", "while", _while);
	else if (exp_type[1] != 0)
		return fail("while expression is a boolean array!\n", "while", _while);

	_while->symbol_type == SYM_BOOL ;
	_while->size = exp_type[1] ;

	while(child != NULL)
	{
		bool ok ;
		if (child->type == AST_BLOCK)
		{
			fprintf(stderr, "entrou visitwhile block\n") ;
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_BLOCK_ELSE)
		{
			fprintf(stderr, "entrou visitwhile blockelse\n") ;
			ok = Symbols_visitBlockElse(st, child);
		}
		else
			ok = fail("Internal compiler error! - while", "!?!?", _while);

		child = child->nextSibling ;

		if(!ok)
			return false ;
	}

	return true ;
}

static bool Symbols_visitReturn(SymbolTable* st, AST* _return) 
{
	int* exp_type ;

	if( _return->firstChild != NULL)
	{
		exp_type  = Symbols_visitExpression(st, _return->firstChild) ;

		if (exp_type[0] == -1)
			return fail("invalid return expression!", "return", _return);
		else if (exp_type[0] == AST_NUMINT)
		{
			_return->symbol_type = SYM_INT ;
			_return->size = exp_type[1] ;
			//COMPARAR COM RETORNO DA FUNCAO
		}
		else if (exp_type[0] == AST_CHAR)
		{
			_return->symbol_type = SYM_CHAR ;
			_return->size = exp_type[1] ;
			//COMPARAR COM RETORNO DA FUNCAO
		}
		else if (exp_type[0] == AST_BOOL)
		{
			_return->symbol_type = SYM_BOOL ;
			_return->size = exp_type[1] ;
			//COMPARAR COM RETORNO DA FUNCAO
		}
		else if (exp_type[0] == AST_ID)
		{
			//COMPARAR COM RETORNO DA FUNCAO
		}
		else
			return fail("Internal compiler error! - return", "!?!?", _return);	
	}
	
	return true ;
}

static bool Symbols_visitNew(SymbolTable* st, AST* _new) 
{
	int* exp_type ;

	exp_type  = Symbols_visitExpression(st, _new->firstChild) ;

	if (exp_type[0] != AST_NUMINT || exp_type[0] != AST_CHAR)
		return fail("invalid \"new\" expression!", "new", _new);

	if (exp_type[0] == AST_NUMINT)
	{
		_new->symbol_type = SYM_INT ;
	}
	else if (exp_type[0] == AST_CHAR)
	{
		_new->symbol_type = SYM_CHAR ;
	}

	//OLHAR TIPO DO NEW
	return true ;
}

static bool Symbols_visitCall(SymbolTable* st, AST* call) 
{
	const char* name = call->firstChild->stringVal;
  	Symbol* existing = SymbolTable_get(st, name);
	AST* child =  call->firstChild->nextSibling;

	const char* param_name ;

  	if (existing) 
	{
      		if (existing->type != SYM_FUN) 
		{
         		return fail("is not a function!", name, call);
      		}

		while (child != NULL)
		{
			Symbols_visitExpression(st, child) ;
			if (child->type == AST_ID)
			{
				param_name = child->stringVal ;
				Symbol* existing_id = SymbolTable_get(st, param_name);

				if(existing_id)
				{
					if (existing_id->type == SYM_FUN) 
         					return fail("is a function!", name, call);
					else
					{
						//COMPARAR COM OS PARAMETROS DA FUNCAO
					}	
				}
			}
			else if (child->type == AST_NUMINT)
			{
				//COMPARAR COM OS PARAMETROS DA FUNCAO
			}
			else if (child->type == AST_CHAR)
			{
				//COMPARAR COM OS PARAMETROS DA FUNCAO
			}
			else if (child->type == AST_BOOL)
			{
				//COMPARAR COM OS PARAMETROS DA FUNCAO
			}
			else
			{
				return fail("Internal compiler error! - call", "!?!?", call);
			}
			child = child->nextSibling;
		}

		call->symbol_type = SYM_FUN ;
      		assert(existing->type == SYM_FUN);
      		return true;
   	}
   	return fail("undeclared function!", name, call);
}


static bool Symbols_visitAssign(SymbolTable* st, AST* assign) 
{
	const char* name = assign->firstChild->stringVal;
   	Symbol* existing = SymbolTable_get(st, name);
	int* assign_type ;

	assign_type = Symbols_visitExpression(st, assign->lastChild);

   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
         		return fail("is a function!", name, assign);

		else if (existing->type == SYM_INT)
		{
			if ((assign_type[0] == AST_NUMINT) || (assign_type[0] == AST_CHAR))
			{
				if(assign_type[1] == existing->size)
				{
					assign->symbol_type = SYM_INT ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_INT ;
					assign->lastChild->size = assign_type[1] ;
					//assert(existing->type == SYM_INT);
					return true;
				}
				else
					return fail("assigned wrong size value to an int variable!", name, assign);
			}
			else
				return fail("assigned invalid value to an int variable!", name, assign);
		}
		
		else if (existing->type == SYM_BOOL)
		{
			if (assign_type[0] == AST_BOOL)
			{
				if(assign_type[1] == existing->size)
				{
					assign->symbol_type = SYM_BOOL ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_BOOL ;
					assign->lastChild->size = assign_type[1] ;
				//	assert(existing->type == SYM_BOOL);
					return true;
				}
				else
					return fail("assigned wrong size value to a bool variable!", name, assign);
			}
			else
				return fail("assigned invalid value to a bool variable!", name, assign);
		}
	
		else if (existing->type == SYM_CHAR)
		{
			if (assign_type[0] == AST_CHAR)
			{
				fprintf(stderr, "assign_type: %d\n", assign_type[1]) ;
				fprintf(stderr, "existing_size: %d\n", existing->size) ;
				if(assign_type[1] == existing->size)
				{
					assign->symbol_type = SYM_CHAR ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_CHAR ;
					assign->lastChild->size = assign_type[1] ;
					//assert(existing->type == SYM_CHAR);
					return true;
				}
				else
					return fail("assigned wrong size value to char variable!1", name, assign);
			}
			else if (assign_type[0] == AST_NUMINT)
			{
				if(assign_type[1] == existing->size)
				{
					/*PEGAR O ULTIMO BITE!!!!!!!!!*/
					assign->symbol_type = SYM_CHAR ;
					//assert(existing->type == SYM_CHAR);
					return true;
				}
				else
					return fail("assigned wrong size value to char variable!2", name, assign);
			}
			else
				return fail("assigned invalid value to char variable!", name, assign);
		}		
		
   	}
   	return fail("undeclared variable!", name, assign);
}


static bool Symbols_visitDeclVar(SymbolTable* st, AST* declvar) 
{
   	const char* name = declvar->firstChild->stringVal;
   	Symbol* existing = SymbolTable_get(st, name);		
	int* ret = (int*)malloc(2*sizeof(int));

   	if (existing) {
      		if (existing->type == SYM_INT || existing->type == SYM_CHAR || existing->type == SYM_BOOL) 
		{
         		return fail("redeclared variable!", name, declvar);
      		}
		else if (existing->type == SYM_FUN) 
		{
         		return fail("is a function!", name, declvar);
      		} 
		else 
		{
	        	return fail("Internal compiler error!", "!?!?", declvar);
      		}
   	}

	if (declvar->firstChild->nextSibling->type == AST_INT)
	{
		fprintf(stderr, "=>declvar recebe int\n") ;
		declvar->symbol_type = SYM_INT ;
		declvar->firstChild->symbol_type = SYM_INT ;
	}

	else if (declvar->firstChild->nextSibling->type == AST_BOOL)
	{
		fprintf(stderr, "=>declvar recebe bool\n") ;
		declvar->symbol_type = SYM_BOOL ;
		declvar->firstChild->symbol_type = SYM_BOOL ;
		fprintf(stderr, "declvar type em bool: %d\n", declvar->symbol_type) ;
	}

	else if (declvar->firstChild->nextSibling->type == AST_CHAR)
	{
		fprintf(stderr, "=>declvar recebe char\n") ;
		declvar->symbol_type = SYM_CHAR ;
		declvar->firstChild->symbol_type = SYM_CHAR ;
		fprintf(stderr, "declvar type em char: %d\n", declvar->symbol_type) ;
	}
	
	else if (declvar->firstChild->nextSibling->type == AST_STRING)
	{
		fprintf(stderr, "=>declvar recebe string\n") ;
		declvar->symbol_type = SYM_CHAR ;
		declvar->firstChild->symbol_type = SYM_CHAR ;
		fprintf(stderr, "declvar type: %d\n", declvar->symbol_type) ;
	}

	ret[0]=-1;
	ret[1]=-1;
	declvar->size = declvar->firstChild->nextSibling->size ;
	if(declvar->firstChild->nextSibling->type == AST_STRING)
		SymbolTable_add(st, name, declvar->symbol_type, declvar->line, declvar->size+1,  symbol_table_scope, 0, 0, ret);
	else
		SymbolTable_add(st, name, declvar->symbol_type, declvar->line, declvar->size, symbol_table_scope, 0, 0, ret);

   	return true;
}

static void Symbols_setParamGlob(SymbolTable* st, AST* parent, AST* child1, AST* child2, int symbol_type) 
{
	const char* name = child1->stringVal;
	int* ret = (int*)malloc(2*sizeof(int));

	parent->symbol_type = symbol_type ;
	parent->size = child2->size ;
	child1->symbol_type = symbol_type ;
	child1->size = child2->size ;
	child2->symbol_type = symbol_type ;

	ret[1]=-1;
	ret[0]=-1;
	SymbolTable_add(st, name, symbol_type, parent->line, child2->size, symbol_table_scope, 0, 0, ret);
}

static bool Symbols_getParamGlob(SymbolTable* st, AST* node) 
{
	fprintf(stderr, "entrou global/parameter\n") ;
	if(node != NULL)
	{
		AST* child1 = node->firstChild ;
		AST* child2 = node->lastChild ;

		if(child2->type == AST_INT)
		{
			Symbols_setParamGlob(st, node, child1, child2, SYM_INT);
		}
		else if (child2-> type == AST_CHAR)
		{
			Symbols_setParamGlob(st, node, child1, child2, SYM_CHAR);
		}
		else if (child2-> type == AST_BOOL)
		{
			Symbols_setParamGlob(st, node, child1, child2, SYM_BOOL);
		}
		else if (child2-> type == AST_STRING)
		{
			Symbols_setParamGlob(st, node, child1, child2, SYM_CHAR);
		}	
		else
		{
			fprintf(stderr, "saiu global/parameter\n") ;
			return fail("Internal compiler error - parameter/global", "!?!?", node);
		}
	}
	fprintf(stderr, "saiu global/parameter\n") ;
	return true ;
}

static bool Symbols_visitParameter(SymbolTable* st, AST* parameter) 
{

	return Symbols_getParamGlob(st, parameter) ; 
}

static bool Symbols_visitGlobal(SymbolTable* st, AST* global) 
{
	return Symbols_getParamGlob(st, global) ;
}

static bool Symbols_visitBlockElse(SymbolTable* st, AST* block_else)
{
	if(block_else != NULL)
	{
		AST* child = block_else->firstChild;

		while (child != NULL)
		{
			bool ok;
			if (child->type == AST_ELSEIF)
			{
				ok = Symbols_visitElseIf(st, child);
			}
			else if (child->type == AST_ELSE)
			{
				ok = Symbols_visitElse(st, child); 
			}
			child = child->nextSibling ;
		}
	}

	return true;
}


static bool Symbols_visitBlock(SymbolTable* st, AST* block)
{
	if(block != NULL)
	{
		AST* child = block->firstChild;

		while (child != NULL)
		{
			bool ok;
        		if (child->type == AST_IF)
			{
				fprintf(stderr, "entrou no if do visit block\n") ;
				ok = Symbols_visitIf(st, child);
				fprintf(stderr, "saiu do if do visit block\n") ;
			}
        		if (child->type == AST_WHILE)
			{
				fprintf(stderr, "while do visit block\n") ;
				ok = Symbols_visitWhile(st, child);
			}
			else if (child->type == AST_CALL) 
			{
				fprintf(stderr, "call do visit block\n") ;
		        	ok = Symbols_visitCall(st, child);
			}
			else if (child->type == AST_RET)
			{
				fprintf(stderr, "entrou ret do visit block\n") ;
				ok = Symbols_visitReturn(st, child);
				fprintf(stderr, "saiu ret do visit block\n") ;
			}
        		else if (child->type == AST_DECLVAR) 
			{
				fprintf(stderr, "declvar do visit block\n") ;
		        	ok = Symbols_visitDeclVar(st, child);
				fprintf(stderr, "declvar type em bloco: %d\n", child->symbol_type) ;
		 	} 
			else if (child->type == AST_ATRIB)
			{
				fprintf(stderr, "atrib do visit block\n") ;
				ok = Symbols_visitAssign(st, child); 
			}
			else 
		        	fail("Internal compiler error! - block", "!?!?", block);

		      	if (!ok) 
		        	return false;
			child = child->nextSibling ;
		}
	}

	return true;	
} 


static bool Symbols_visitFunction(SymbolTable* st, AST* function) 
{
	const char* name = function->stringVal;
	AST* child = function->firstChild;
	int qtd_params = 0, cont = 0 ;
	int armazena_params [50] ;
	int* lista_tipos_params ;
	int ret[2] ; /* ret_tipo[0] = tipo de retorno ; ret_tipo[1] == tamanho do array */


	fprintf(stderr, "entrou1\n") ;
	Symbol* existing = SymbolTable_get(st, name);
	fprintf(stderr, "pass1\n") ;
	if (existing) 
	{
      	   	return fail("redeclared function!\n", name, function);
	}

	//SymbolTable_beginScope(st);

	while (child != NULL)
	//for(AST* child = function->firstChild; child; child = child->nextSibling) 
	{
		bool ok;   	
      
		if (child->type == AST_PARAM)
		{
			fprintf(stderr, "param\n") ;
			ok = Symbols_visitParameter(st, child);
			armazena_params[qtd_params] = child->lastChild->type ; 
			qtd_params++ ;
		}
		else if (child->type == AST_BLOCK)
		{
			fprintf(stderr, "bloco\n") ;
			ok = Symbols_visitBlock(st, child);
			fprintf(stderr, "saiu bloco da funcao\n") ;
		}
		else if (child->type == AST_INT)
		{
			fprintf(stderr, "int\n") ;
			ret[0] = SYM_INT ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_INT, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
			fprintf(stderr, "saiu int\n") ;
		}
		else if (child->type == AST_CHAR || child->type == AST_STRING)
		{
			fprintf(stderr, "char/string\n") ;
			ret[0] = SYM_CHAR ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_CHAR, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
		}
		else if (child->type == AST_BOOL)
		{
			fprintf(stderr, "bool\n") ;
			ret[0] = SYM_BOOL ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_BOOL, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
		}
		else 
	        	fail("Internal compiler error! - function", "!?!?", function);
      		
      		if (!ok) 
	        	return false;

		 child = child->nextSibling ;
	        
   	}

	lista_tipos_params = (int*)malloc(qtd_params*sizeof(int));
	//VER O TAMANHO DO ARRAY DE CADA PARAMETRO
	while (cont < qtd_params)
	{
		lista_tipos_params[cont] = armazena_params[cont];
		cont++;
	}

	SymbolTable_add(st, name, SYM_FUN, function->line, function->size,  symbol_table_scope, qtd_params, lista_tipos_params, ret);
	//SymbolTable_endScope(st);
	fprintf(stderr, "saiu fun\n") ;
	return true;
}

bool Symbols_annotate(AST* program) 
{
	SymbolTable* st = SymbolTable_new();
	AST* child = program->firstChild;
	fprintf(stderr, "passou\n") ;

	symbol_table_scope = -1;

	while(child != NULL)
	//for(AST* child = program->firstChild; child; child = child->nextSibling) 
	{
		if (child->type == AST_FUN)
		{
			fprintf(stderr, "funcao\n") ;
        		bool ok = Symbols_visitFunction(st, child);

        		if (!ok) 
			{
        			return false;
      			}
		}
		else if (child->type == AST_GLOBAL)
		{
			fprintf(stderr, "global\n") ;
        		bool ok = Symbols_visitGlobal(st, child);
        		if (!ok) 
			{
        			return false;
      			}
		}
		else if (child->type == 0)
		{
			return true ;
		}
		else
		{
			fail("Internal compiler error! - program", "!?!?", child);
		}
		child = child->nextSibling ;
   	}


   return true;
}


void Symbols_printSYM (int type)
{
	if (type == SYM_INT)
		 fprintf(stdout, " -- SYM_INT");
	else if (type == SYM_CHAR)
		fprintf(stdout, " -- SYM_CHAR");
	else if (type == SYM_BOOL)
		fprintf(stdout, " -- SYM_BOOL");
	else if (type == SYM_FUN)
		fprintf(stdout, " -- SYM_FUN");
	else if (type == -1)
		fprintf(stdout, " -- -------");
}


