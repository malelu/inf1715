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

static int Symbols_visitExpression(SymbolTable* st, AST* exp) 
{

	int child1, child2 ;
	const char* name = exp->stringVal;

	if (exp->type == AST_NUMINT)
	{
		exp->symbol_type = SYM_INT ;
		return AST_NUMINT ;
	}
	else if (exp->type == AST_LITERAL_STRING)
	{
		return AST_LITERAL_STRING ;
	}
	else if (exp->type == AST_TRUE || exp->type == AST_FALSE)
	{
		exp->symbol_type = SYM_BOOL ;
		return AST_BOOL ;
	}
	else if (exp->type == AST_ID)
	{
		Symbol* existing = SymbolTable_get(st, name);

		if (existing->type == SYM_INT)
		{
			exp->symbol_type = SYM_INT ;
			return AST_NUMINT ;
		}
		else if (existing->type == SYM_BOOL)
		{
			exp->symbol_type = SYM_BOOL ;
			return AST_BOOL ;
		}
		else if (existing->type == SYM_CHAR )
		{
			exp->symbol_type = SYM_CHAR ;
			return AST_CHAR ;
		}
		/* ELSE IF PARA TRATAR ARRAY DE CHAR */
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

		if(((child1 == AST_NUMINT) || (child1 == AST_CHAR)) && ((child2 == AST_NUMINT) || (child2 = AST_CHAR)))
		{
			exp->symbol_type = SYM_INT ;
			return AST_NUMINT ;
		}
		else
		{
			fprintf(stderr, "invalid expression! - %s at line %d", "+ - * /", exp->line);
			return -1 ;
		}
	}

	else if (exp->type == AST_GREATER || exp->type == AST_LESS || exp->type == AST_GREATER_EQUAL 
		 || exp->type == AST_LESS_EQUAL || exp->type == AST_EQUAL || exp->type == AST_NOT_EQUAL)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if(((child1 == AST_NUMINT) || (child1 == AST_CHAR)) && ((child2 == AST_NUMINT) || (child2 = AST_CHAR)))
		{
			exp->symbol_type = SYM_BOOL ;
			return AST_BOOL ;
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

		if(child1 == AST_BOOL && child2 == AST_BOOL)
		{
			exp->symbol_type = SYM_BOOL ;
			return AST_BOOL ;
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

		if(child1 == AST_BOOL)
		{
			exp->symbol_type = SYM_BOOL ;
			return AST_BOOL ;
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

		if(child1 == AST_NUMINT || child1 == AST_CHAR)
		{
			exp->symbol_type = SYM_INT ;
			return AST_NUMINT ;
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
   		SymbolTable_add(st, name, SYM_INT, declvar->line, 0, 0, 0);
	}

	else if (declvar->firstChild->nextSibling->type == AST_BOOL)
	{
		declvar->symbol_type = SYM_BOOL ;
		SymbolTable_add(st, name, SYM_BOOL, declvar->line, 0, 0, 0);
	}

	else if (declvar->firstChild->nextSibling->type == AST_CHAR)
	{
		declvar->symbol_type = SYM_CHAR ;
		SymbolTable_add(st, name, SYM_CHAR, declvar->line, 0, 0, 0);
	}

   	return true;
}

static bool Symbols_visitParameter(SymbolTable* st, AST* parameter) 
{
	return Symbols_visitDeclVar(st, parameter);
}

static bool Symbols_visitGlobal(SymbolTable* st, AST* global) 
{
	return Symbols_visitDeclVar(st, global);
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
		else if (child->type == AST_CALL) 
		{
	        	ok = Symbols_visitCall(st, child);
		}
		else if (child->type == AST_ELSEIF)
		{
			ok = Symbols_visitElseIf(st, child);
		}
		else if (child->type == AST_RET)
		{
			ok = Symbols_visitReturn(st, child);
		}
        	else if (child->type == AST_DECLVAR) 
		{
	        	ok = Symbols_visitDeclVar(st, child);
	 	} 
		else if (child->type == AST_ELSE)
		{
			ok = Symbols_visitElse(st, child) 
		}
		child = child->nextSibling ;
	}

	return true;	
} 


static bool Symbols_visitFunction(SymbolTable* st, AST* function) 
{
	const char* name = function->stringVal;
	AST* child = function->firstChild;
fprintf(stderr, "entrou1\n") ;
	Symbol* existing = SymbolTable_get(st, name);
fprintf(stderr, "pass1\n") ;
	if (existing) 
	{
      	   	return fail("redeclared function!\n", name, function);
	}
fprintf(stderr, "passou1\n") ;
	SymbolTable_add(st, name, SYM_FUN, function->line);
	//SymbolTable_beginScope(st);

	while (child != NULL)
	//for(AST* child = function->firstChild; child; child = child->nextSibling) 
	{
		bool ok;
        	if (child->type == AST_DECLVAR) 
	{
fprintf(stderr, "entrou1\n") ;
	        	ok = Symbols_visitDeclVar(st, child);
	 }     	
		else if (child->type == AST_ATRIB) 
{
fprintf(stderr, "entrou1\n") ;
	        	ok = Symbols_visitAssign(st, child);
}	      	
		else if (child->type == AST_CALL) 
{
fprintf(stderr, "entrou1\n") ;
	        	ok = Symbols_visitCall(st, child);
}        	
		else if (child->type == AST_IF)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitIf(st, child);
}
		else if (child->type == AST_ELSEIF)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitElseIf(st, child);
}
		else if (child->type == AST_WHILE)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitWhile(st, child);
}
		else if (child->type == AST_RET)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitReturn(st, child);
}
		else if (child->type == AST_NEW)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitNew(st, child);
}

		else if (child->type == AST_PARAM)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitParameter(st, child);
}

		else if (child->type == AST_GLOBAL)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitGlobal(st, child);
}

		else if (child->type == AST_BLOCK || child->type == AST_BLOCK_ELSE)
{
fprintf(stderr, "entrou1\n") ;
			ok = Symbols_visitBlock(st, child);
}

		else 
	        	fail("Internal compiler error!", "!?!?", function);
      		
      		if (!ok) 
	        	return false;

		 child = child->nextSibling ;
	        
   	}
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
        	bool ok = Symbols_visitFunction(st, child);
        	if (!ok) 
		{
        		return false;
      		}
		child = child->nextSibling ;
   	}
   return true;
}


