#include "tabela_simbolos.h"
#include "simbolos.h"
#include "ast.h"
#include <stdio.h>



static bool fail(const char* msg, const char* name, AST* node) 
{
   	fprintf(stderr, "%s - %s at line %d", msg, name, node->line);
   	return false;
}

int Symbols_visitExpression(SymbolTable* st, AST* exp) 
{

	int child1, child2 ;
	if (exp->type == AST_NUMINT)
	{
		return AST_NUMINT ;
	}
	else if (exp->type == AST_ID)
	{
		return AST_ID ;
	}
	else if (exp->type == AST_BOOL)
	{
		return AST_BOOL ;
	}

	else if (exp->type == AST_PLUS || exp->type == AST_MINUS || exp->type == AST_TIMES || exp->type == AST_DIVIDED)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if((child1 == AST_NUMINT || child1 == AST_CHAR) && (child2 == AST_NUMINT || child2 = AST_CHAR)
			return AST_NUMINT ;

		else
			return fail("invalid expression!", "?????????", exp);
	}

	else if (exp->type == AST_GREATER || exp->type == AST_LESS || exp->type == AST_GREATER_EQUAL 
		 || exp->type == AST_LESS_EQUAL || exp->type == AST_EQUAL || exp->type == AST_NOT_EQUAL)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if((child1 == AST_NUMINT || child1 == AST_CHAR) && (child2 == AST_NUMINT || child2 = AST_CHAR)
			return AST_BOOL ;

		else
			return fail("invalid comparison expression!", "?????????", exp);
	}

	else if (exp->type == AST_AND || exp->type == AST_OR)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;
		child2 = Symbols_visitExpression(st, exp->lastChild) ;

		if(child1 == AST_BOOL && child2 == AST_BOOL)
			return AST_BOOL ;

		else
			return fail("invalid and/or expression!", "?????????", exp);
	}

	else
		return fail("invalid expression!", "?????????", exp);
}


static bool Symbols_visitIf(SymbolTable* st, AST* _if) 
{
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

	assign_type = Symbols_visitExpression(SymbolTable* st, AST* exp)

   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
         		return fail("is a function!", name, assign);

		else if (existing->type == SYM_INT)
		{
			if (assign_type == AST_NUMINT or assign_type = AST_CHAR)
			{
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
				assert(existing->type == SYM_CHAR);
				return true;
			}
			else if (assign_type == AST_NUMINT)
			{
				/*PEGAR O ULTIMO BITE!!!!!!!!!*/
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
	        	fail("Internal compiler error!", "!?!?", declvar);
      		}
   	}

	if (declvar->firstChild->nextSibling->type == AST_INT)
   		SymbolTable_add(st, name, SYM_INT, declvar->line);

	else if (declvar->firstChild->nextSibling->type == AST_BOOL)
		SymbolTable_add(st, name, SYM_BOOL, declvar->line);

	else
		SymbolTable_add(st, name, SYM_CHAR, declvar->line);

   	return true;
}

static bool Symbols_visitFunction(SymbolTable* st, AST* function) 
{
	const char* name = function->stringVal;

	Symbol* existing = SymbolTable_get(st, name);
	if (existing) 
	{
      	   	return fail("redeclared function!", name, function);
	}

	SymbolTable_add(st, name, SYM_FUN, function->line);
	SymbolTable_beginScope(st);

	for(AST* child = function->firstChild; child; child = child->nextSibling) 
	{
		bool ok;
        	if (child->type == AST_DECLVAR) 
		{
	        	ok = Symbols_visitDeclVar(st, child);
	      	} 
		else if (child->type == AST_ASSIGN) 
		{
	        	ok = Symbols_visitAssign(st, child);
	      	} 
		else if (child->type == AST_CALL) 
		{
	        	ok = Symbols_visitCall(st, child);
        	} 
		else 
		{
	        	fail("Internal compiler error!", "!?!?", function);
      		}
      		if (!ok) 
		{
	        	return false;
	        }
   	}
	SymbolTable_endScope(st);
	return true;
}

bool Symbols_annotate(AST* program) 
{
	SymbolTable* st = SymbolTable_new();
	for(AST* child = program->firstChild; child; child = child->nextSibling) 
	{
        	bool ok = Symbols_visitFunction(st, child);
        	if (!ok) 
		{
        		return false;
      		}
   	}
   return true;
}


