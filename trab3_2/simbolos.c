#include "tabela_simbolos.h"
#include "simbolos.h"
#include "ast.h"
#include <stdio.h>
#include <assert.h>



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
	int* ret_expression = (int*)malloc(2*sizeof(int)) ;   /* pos[0] = tipo ; pos[1] = tamanho do array */
	int* child1 = (int*)malloc(2*sizeof(int)) ;
	int* child2 = (int*)malloc(2*sizeof(int)) ;
	const char* name = exp->stringVal;

	if (exp->type == AST_NUMINT)
	{
		return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, exp->size);
	}
	else if (exp->type == AST_LITERAL_STRING)
	{
		return Symbols_setExpression (ret_expression, exp, SYM_CHAR, AST_CHAR, exp->size);
	}
	else if (exp->type == AST_TRUE || exp->type == AST_FALSE)
	{
		return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, exp->size);
	}
	else if (exp->type == AST_ID)
	{
		Symbol* existing = SymbolTable_get(st, name);

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
		else
		{
			fprintf(stderr, "undeclared variable! - %s at line %d", name, exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_PLUS || exp->type == AST_MINUS || exp->type == AST_TIMES || exp->type == AST_DIVIDED)
	{
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
				fprintf(stderr, "invalid expression! Invalid type sizes! - %s at line %d", "+ - * /", exp->line);
				return -1 ;
			}
		}
		else
		{
			fprintf(stderr, "invalid expression! Invalid types! - %s at line %d", "+ - * /", exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_GREATER || exp->type == AST_LESS || exp->type == AST_GREATER_EQUAL 
		 || exp->type == AST_LESS_EQUAL || exp->type == AST_EQUAL || exp->type == AST_NOT_EQUAL)
	{
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
				fprintf(stderr, "invalid comparison expression! Invalid type sizes! - %s at line %d", "comparison", exp->line);
				return -1 ;
			}
		}
		else
		{
			fprintf(stderr, "invalid comparison expression! - %s at line %d", "comparison", exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_AND || exp->type == AST_OR)
	{
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
				fprintf(stderr, "invalid and/or expression! Invalid type sizes! - %s at line %d", "and/or", exp->line);
				return -1 ;
			}
		}

		else
		{
			fprintf(stderr, "invalid and/or expression! - %s at line %d", "and/or", exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_NOT)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(child1[0] == AST_BOOL && child1[1] == 0)
		{
			return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0);
		}

		else
		{
			fprintf(stderr, "invalid \"not\" expression! - %s at line %d", "not", exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_NEG)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(((child1[0] == AST_NUMINT) && (child1[1] == 0)) || ((child1[0] == AST_CHAR) && (child1[1] == 0)))
		{
			return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, 0);
		}

		else
		{
			fprintf(stderr, "invalid - expression! - %s at line %d", "neg", exp->line);
			return -1 ;
		}
	}

	fprintf(stderr, "invalid expression! - %s at line %d", "exp", exp->line);
	return -1 ;
}


static bool Symbols_visitIf(SymbolTable* st, AST* _if) 
{
	int exp_type ;

	exp_type  = Symbols_visitExpression(st, _if->firstChild) ;

	if (exp_type != AST_BOOL)
		return fail("if expression is not a boolean value!", "if", _if);

	_if->symbol_type == SYM_BOOL ;
	return true ;
}

static bool Symbols_visitElseIf(SymbolTable* st, AST* else_if) 
{
	int exp_type ;

	exp_type  = Symbols_visitExpression(st, else_if->firstChild) ;

	if (exp_type != AST_BOOL)
		return fail("else if expression is not a boolean value!", "else if", else_if);

	else_if->symbol_type == SYM_BOOL ;
	return true ;
}


static bool Symbols_visitElse(SymbolTable* st, AST* else_if) 
{
	int exp_type ;
//FAZEEEEEEEEEEEEEEEEER
	return true ;
}

static bool Symbols_visitWhile(SymbolTable* st, AST* _while) 
{
	int exp_type ;

	exp_type  = Symbols_visitExpression(st, _while->firstChild) ;

	if (exp_type != AST_BOOL)
		return fail("while expression is not a boolean value!", "while", _while);

	_while->symbol_type == SYM_BOOL ;
	return true ;
}

static bool Symbols_visitReturn(SymbolTable* st, AST* _return) 
{
	int exp_type ;

	if( _return->firstChild != NULL)
	{
		exp_type  = Symbols_visitExpression(st, _return->firstChild) ;

		if (exp_type == -1)
			return fail("invalid return expression!", "return", _return);
		return true ;
	}
}

static bool Symbols_visitNew(SymbolTable* st, AST* _new) 
{
	int exp_type ;

	exp_type  = Symbols_visitExpression(st, _new->firstChild) ;

	if (exp_type != AST_NUMINT || exp_type != AST_CHAR)
		return fail("invalid \"new\" expression!", "new", _new);

	if (exp_type == AST_NUMINT)
	{
		_new->symbol_type = SYM_INT ;
	}
	else if (exp_type == AST_CHAR)
	{
		_new->symbol_type = SYM_CHAR ;
	}
	return true ;
}

static bool Symbols_visitCall(SymbolTable* st, AST* call) 
{
	const char* name = call->firstChild->stringVal;
  	Symbol* existing = SymbolTable_get(st, name);
  	if (existing) 
	{
      		if (existing->type != SYM_FUN) 
		{
         		return fail("is not a function!", name, call);
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
	int assign_type ;

	assign_type = Symbols_visitExpression(st, assign->lastChild);

   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
         		return fail("is a function!", name, assign);

		else if (existing->type == SYM_INT)
		{
			if ((assign_type == AST_NUMINT) || (assign_type == AST_CHAR))
			{
				assign->symbol_type = SYM_INT ;
				assert(existing->type == SYM_INT);
				return true;
			}
			else
				return fail("assigned invalid value to an int variable!", name, assign);
		}
		
		else if (existing->type == SYM_BOOL)
		{
			if (assign_type == AST_BOOL)
			{
				assign->symbol_type = SYM_BOOL ;
				assert(existing->type == SYM_BOOL);
				return true;
			}
			else
				return fail("assigned invalid value to a bool variable!", name, assign);
		}
	
		else if (existing->type == SYM_CHAR)
		{
			if (assign_type == AST_CHAR)
			{
				assign->symbol_type = SYM_CHAR ;
				assert(existing->type == SYM_CHAR);
				return true;
			}
			else if (assign_type == AST_NUMINT)
			{
				/*PEGAR O ULTIMO BITE!!!!!!!!!*/
				assign->symbol_type = SYM_CHAR ;
				assert(existing->type == SYM_CHAR);
				return true;
			}
			else
				return fail("assigned invalid value to char variable!", name, assign);
		}
		/* FAZER ELSE IF DO ARRAY DE CHAR! */		
		
   	}
   	return fail("undeclared variable!", name, assign);
}


static bool Symbols_visitDeclVar(SymbolTable* st, AST* declvar) 
{
   	const char* name = declvar->firstChild->stringVal;
   	Symbol* existing = SymbolTable_get(st, name);
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
		declvar->symbol_type = SYM_INT ;
   		SymbolTable_add(st, name, SYM_INT, declvar->line, declvar->size, 0, 0, 0);
	}

	else if (declvar->firstChild->nextSibling->type == AST_BOOL)
	{
		declvar->symbol_type = SYM_BOOL ;
		SymbolTable_add(st, name, SYM_BOOL, declvar->line, declvar->size, 0, 0, 0);
	}

	else if (declvar->firstChild->nextSibling->type == AST_CHAR)
	{
		declvar->symbol_type = SYM_CHAR ;
		SymbolTable_add(st, name, SYM_CHAR, declvar->line, declvar->size, 0, 0, 0);
	}

   	return true;
}

static void Symbols_visitParameter(SymbolTable* st, AST* parameter, AST* child1, AST* child2, int symbol_type) 
{
	const char* name = child1->stringVal;

	parameter->symbol_type = symbol_type ;
	parameter->size = child2->size ;
	child1->symbol_type = symbol_type ;
	child1->size = child2->size ;
	child2->symbol_type = symbol_type ;
	SymbolTable_add(st, name, symbol_type, parameter->line, child2->size, 0, 0, 0);
}


static bool Symbols_visitParameter(SymbolTable* st, AST* parameter) 
{
	if(parameter != NULL)
	{
		AST* child1 = parameter->firstChild ;
		AST* child2 = parameter->lastChild ;

		if(child2->type == AST_INT)
		{
			Symbols_visitParameter(st, parameter, child1, child2, SYM_INT);
		}
		else if (child2-> type == AST_CHAR)
		{
			Symbols_visitParameter(st, parameter, child1, child2, SYM_CHAR);
		}
		else if (child2-> type == AST_BOOL)
		{
			Symbols_visitParameter(st, parameter, child1, child2, SYM_BOOL);
		}
		else if (child2-> type == AST_STRING)
		{
			Symbols_visitParameter(st, parameter, child1, child2, SYM_CHAR);
		}	
		else
		{
			return fail("Internal compiler error - parameter!", "!?!?", parameter);
		}

		return true ;


	exp->symbol_type = SymbolType ;
	exp->size = size ;
	}
}

static bool Symbols_visitGlobal(SymbolTable* st, AST* global) 
{
	return Symbols_visitDeclVar(st, global);
}

static bool Symbols_visitBlockElse(SymbolTable* st, AST* block)
{
	AST* child = block->firstChild;

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

	return true;
}


static bool Symbols_visitBlock(SymbolTable* st, AST* block)
{
	AST* child = block->firstChild;

	while (child != NULL)
	{
		bool ok;
        	if (child->type == AST_IF)
		{
			ok = Symbols_visitIf(st, child);
		}
        	if (child->type == AST_WHILE)
		{
			ok = Symbols_visitWhile(st, child);
		}
		else if (child->type == AST_CALL) 
		{
	        	ok = Symbols_visitCall(st, child);
		}
		else if (child->type == AST_RET)
		{
			ok = Symbols_visitReturn(st, child);
		}
        	else if (child->type == AST_DECLVAR) 
		{
	        	ok = Symbols_visitDeclVar(st, child);
	 	} 
		else if (child->type == AST_ATRIB)
		{
			ok = Symbols_visitAssign(st, child); 
		}
		else 
	        	fail("Internal compiler error! - block", "!?!?", function);

	      	if (!ok) 
	        	return false;
		child = child->nextSibling ;
	}

	return true;	
} 


static bool Symbols_visitFunction(SymbolTable* st, AST* function) 
{
	const char* name = function->stringVal;
	AST* child = function->firstChild;
	int qtd_params = 0 ;
	int armazena_params [50] ;
	int* lista_tipos_params ;
	int ret_tipo[2] ; /* ret_tipo[0] = tipo de retorno ; ret_tipo[1] == tamanho do array */


	fprintf(stderr, "entrou1\n") ;
	Symbol* existing = SymbolTable_get(st, name);
	fprintf(stderr, "pass1\n") ;
	if (existing) 
	{
      	   	return fail("redeclared function!\n", name, function);
	}
	fprintf(stderr, "passou1\n") ;

	//SymbolTable_beginScope(st);

	while (child != NULL)
	//for(AST* child = function->firstChild; child; child = child->nextSibling) 
	{
		bool ok;   	
      
		if (child->type == AST_PARAM)
		{
			fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitParameter(st, child);
			armazena_params[qtd_params] = child->lastChild->type ; 
			qtd_params++ ;
		}
		else if (child->type == AST_BLOCK)
		{
			fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_INT)
		{
			fprintf(stderr, "entrou1\n") ;
			ret[0] = SYM_INT ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_INT, child->line, child->size, 0, 0, 0);
			ok = true ;
		}
		else if (child->type == AST_CHAR || child->type == AST_STRING)
		{
			fprintf(stderr, "entrou1\n") ;
			ret[0] = SYM_CHAR ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_CHAR, child->line, child->size, 0, 0, 0);
			ok = true ;
		}
		else if (child->type == AST_BOOL)
		{
			fprintf(stderr, "entrou1\n") ;
			ret[0] = SYM_BOOL ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_BOOL, child->line, child->size, 0, 0, 0);
			ok = true ;
		}
		else 
	        	fail("Internal compiler error!", "!?!?", function);
      		
      		if (!ok) 
	        	return false;

		 child = child->nextSibling ;
	        
   	}

	lista_tipos_params = (int*)malloc(qtd_params*sizeof(int))
	//VER O TAMANHO DO ARRAY DE CADA PARAMETRO
	while (cont < qtd_params)
	{
		lista_tipos_params[cont] = armazena_params[cont]
	}

	SymbolTable_add(st, name, SYM_FUN, function->line, function->size, qtd_params, lista_tipos_params, ret);
	//SymbolTable_endScope(st);
	return true;
}

bool Symbols_annotate(AST* program) 
{
	SymbolTable* st = SymbolTable_new();
	AST* child = program->firstChild;
	fprintf(stderr, "passou\n") ;
	while(child != NULL)
	//for(AST* child = program->firstChild; child; child = child->nextSibling) 
	{

		if (child->type = AST_FUN)
		{
        		bool ok = Symbols_visitFunction(st, child);
        		if (!ok) 
			{
        			return false;
      			}
		}
		else if (child->type = AST_GLOBAL)
		{
        		bool ok = Symbols_visitGlobal(st, child);
        		if (!ok) 
			{
        			return false;
      			}
		}
		else if (child->type == NULL)
		{
			return true ;
		}
		else
		{
			fail("Internal compiler error!", "!?!?", child);
		}
		child = child->nextSibling ;
   	}
   return true;
}


