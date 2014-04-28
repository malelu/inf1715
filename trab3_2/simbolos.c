#include "simbolos.h"
#include "tabela_simbolos.h"
#include <stdio.h>



static bool fail(const char* msg, const char* name, AST* node) 
{
   	fprintf(stderr, "%s - %s at line %d", msg, name, node->line);
   	return false;
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


static bool Symbols_visitAssignInt(AST* assign, char* name, Symbol* existing)
{
	/* atribuicao de int recebe int */
	if (assign->lastChild->type == 320)
	{
		assert(existing->type == SYM_INT);
		return true;
	}
		
	/* atribuicao de int recebe bool */
	else if (assign->lastChild->type == 287 || assign->lastChild->type == 288)
	{
		return fail("assigned bool to an int variable!", name, assign);
	}
	/* atribuicao de int recebe char ou string VEEEEEEEEEEEEER*/
	else if (assign->lastChild->type == 309)
	{
		assert(existing->type == SYM_INT);
			return true;
	}
}


static bool Symbols_visitAssign(SymbolTable* st, AST* assign) 
{
	const char* name = assign->firstChild->stringVal;
   	Symbol* existing = SymbolTable_get(st, name);
   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
		{
         		return fail("is a function!", name, assign);
      		}

		if (existing->type == SYM_INT)
		{
			return Symbols_visitAssignInt(assign, name, existing) ;
		}
		/* atribuicao de int recebe int */
		if (existing->type == SYM_INT && assign->lastChild->type == 320)
		{
			assert(existing->type == SYM_INT);
			return true;
		}
			
		/* atribuicao de int recebe bool */
		else if (existing->type == SYM_INT && assign->lastChild->type == 287 || 
			  existing->type == SYM_INT && assign->lastChild->type == 288)
		{
			return fail("assigned bool to an int variable!", name, assign);
		}
		/* atribuicao de int recebe char ou string */
		else if (existing->type == SYM_INT && assign->lastChild->type == 309)
		{
			assert(existing->type == SYM_INT);
			return true;
		}


	      	assert(existing->type == SYM_INT);
	      	return true;
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

	//colocar para todos os simbolos
   	SymbolTable_add(st, name, SYM_INT, declvar->line);
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


