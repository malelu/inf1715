#include "simbolos.h"
#include "tabela_simbolos.h"
#include "ast.h"
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
	/* int recebe int */
	if (assign->lastChild->type == 320)
	{
		if(assign->lastChild->intValue >= -2147483648 && (assign->lastChild->intValue <= -2147483647)
		{
			assert(existing->type == SYM_INT);
			return true;
		}
		else
			return fail("assigned integer out of range", name, assign);
	}
		
	/* int recebe bool */
	else if (assign->lastChild->type == 287 || assign->lastChild->type == 288)
	{
		return fail("assigned bool to an int variable!", name, assign);
	}
	/* int recebe char ou string VEEEEEEEEEEEEER*/
	else if (assign->lastChild->type == 309)
	{
		assert(existing->type == SYM_INT);
			return true;
	}

	else
	{
		return fail("assigned non valid value to an int variable!", name, assign);
	}
}


static bool Symbols_visitAssignBool(AST* assign, char* name, Symbol* existing)
{
	/* bool recebe bool */
	if (assign->lastChild->type == 287 || assign->lastChild->type == 288)
	{
		assert(existing->type == SYM_BOOL);
		return true;
	}
	/* bool recebe int */
	else if (assign->lastChild->type == 320)
		return fail("assigned int to a bool variable!", name, assign);

	/* bool recebe char ou string */
	else if (assign->lastChild->type == 309)
		return fail("assigned char to a bool variable!", name, assign);

	else
		return fail("assigned non valid value to a bool variable!", name, assign);
}



/* TRATAR O NUMERO DE CARACTERES!!! */
static bool Symbols_visitAssignChar(AST* assign, char* name, Symbol* existing)
{
	/* char recebe char */
	if (assign->lastChild->type == 309)
	{
		assert(existing->type == SYM_CHAR);
		return true;
	}

	/* char recebe int */
	else if (assign->lastChild->type == 320)

		if (assign->lastChild->intVal >= -127 && assign->lastChild->intVal <= 128)
		{
			assert(existing->type == SYM_CHAR);
			return true;
		}
		else
			return fail("assigned int to a char variable! Undefined", name, assign);

	/* char recebe bool */
	else if (assign->lastChild->type == 287 || assign->lastChild->type == 288)
		return fail("assigned bool to a char variable!", name, assign);

	else
		return fail("assigned non valid value to a char variable!", name, assign);
}


static bool Symbols_visitAssign(SymbolTable* st, AST* assign) 
{
	const char* name = assign->firstChild->stringVal;
   	Symbol* existing = SymbolTable_get(st, name);

   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
         		return fail("is a function!", name, assign);

		else if (existing->type == SYM_INT)
			return Symbols_visitAssignInt(assign, name, existing) ;
		
		else if (existing->type == SYM_BOOL)
			return Symbols_visitAssignBool(assign, name, existing) ;
		
		else if (existing->type == SYM_CHAR)
			return Symbols_visitAssignChar(assign, name, existing) ;		
		
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


