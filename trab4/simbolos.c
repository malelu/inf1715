#include "tabela_simbolos.h"
#include "simbolos.h"
#include "ast.h"
#include <stdio.h>
#include <assert.h>

static bool fail(const char* msg, const char* name, AST* node);
static int* Symbols_setExpression (int* ret_expression, AST* exp, int SymbolType, int ASTtype, int size, int val);
static int* Symbols_visitExpression(SymbolTable* st, AST* exp);
static bool Symbols_visitConditional(SymbolTable* st, AST* node);
static bool Symbols_visitIf(SymbolTable* st, AST* _if); 
static bool Symbols_visitElseIf(SymbolTable* st, AST* else_if); 
static bool Symbols_visitElse(SymbolTable* st, AST* _else); 
static bool Symbols_visitWhile(SymbolTable* st, AST* _while);
static bool Symbols_setReturn(SymbolTable* st, AST* _return, int Symbol_type, int* exp_result);
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
static int returned ;
static int has_return ;
static bool okGlobal = true;

static bool fail(const char* msg, const char* name, AST* node) 
{
   	fprintf(stderr, "%s - %s at line %d\n", msg, name, node->line);
   	return false;
}


static int* Symbols_setExpression (int* ret_expression, AST* exp, int SymbolType, int ASTtype, int size, int val)
{
	exp->symbol_type = SymbolType ;
	exp->size = size ;
	ret_expression[0] = ASTtype ;
	ret_expression[1] = size ;
	ret_expression[2] = val ;
	return ret_expression ;
}

static int* Symbols_visitExpression(SymbolTable* st, AST* exp) 
{
	int* ret_expression = (int*)malloc(3*sizeof(int)) ;   /* pos[0] = tipo ; pos[1] = tamanho do array ; pos[2] = valor do resultado */
	int* child1 = (int*)malloc(3*sizeof(int)) ;
	int* child2 = (int*)malloc(3*sizeof(int)) ;
	const char* name = exp->stringVal;

	if (exp->type == AST_NUMINT)
	{
		return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, exp->size, exp->intVal);
	}
	else if (exp->type == AST_LITERAL_STRING)
	{
		return Symbols_setExpression (ret_expression, exp, SYM_CHAR, AST_CHAR, exp->size, exp->intVal);
	}
	else if (exp->type == AST_TRUE || exp->type == AST_FALSE)
	{
		fprintf(stderr, "visit true\n") ;
		return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, exp->size, exp->intVal);
	}
	else if (exp->type == AST_NEW)
	{
		fprintf(stderr, "visit exp new\n") ;
		okGlobal = Symbols_visitNew(st, exp) ; 
		return Symbols_setExpression (ret_expression, exp, exp->symbol_type, exp->type, exp->size, exp->intVal);
	}
	else if (exp->type == AST_ID)
	{
		Symbol* existing = SymbolTable_get(st, name, symbol_table_scope);

		if(existing)
		{
			if (existing->type == SYM_INT)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, exp->size, exp->intVal);
			}
			else if (existing->type == SYM_BOOL)
			{
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, exp->size, exp->intVal);
			}
			else if (existing->type == SYM_CHAR )
			{
				return Symbols_setExpression (ret_expression, exp, SYM_CHAR, AST_CHAR, exp->size, exp->intVal);
			}
		}

		ret_expression[0]=-1 ;
		ret_expression[1]=-1 ;
		fprintf(stderr, "undeclared variable! - %s at line %d\n", name, exp->line);
		exit(1);

	}

	else if (exp->type == AST_PLUS || exp->type == AST_MINUS || exp->type == AST_TIMES || exp->type == AST_DIVIDED)
	{
		if(exp->firstChild->type == AST_ID && exp->firstChild->size > 0)  // se for vetor, pega o proximo dps do vetor
		{
			int cont = 0 ;
			AST* begNext = exp->firstChild->nextSibling ;
			while(cont < exp->firstChild->size)
			{
				begNext = begNext->nextSibling ;
				cont++ ;
			}

			//child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child1[0] = exp->firstChild->nextSibling->type ;
			child1[1] = exp->size ;
			child2 = Symbols_visitExpression(st, begNext) ;
		}
		else
		{
			child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child2 = Symbols_visitExpression(st, exp->lastChild) ;
		}

		if(((child1[0] == AST_NUMINT) || (child1[0] == AST_CHAR)) && ((child2[0] == AST_NUMINT) || (child2[0] == AST_CHAR)))
		{
			if((child1[1] == child2[1]) && (child1[1] == 0))
			{
				if (exp->type == AST_PLUS)
					return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, child1[1], child1[2] + child2[2]);
				else if (exp->type == AST_MINUS)
					return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, child1[1], child1[2] - child2[2]);
				else if (exp->type == AST_TIMES)
					return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, child1[1], child1[2] * child2[2]);
				else if (exp->type == AST_DIVIDED)
					return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, child1[1], child1[2] / child2[2]);
			}
			else
			{
				printf("child1[1]: %d\n", child1[1]) ;
				printf("child1[1]: %d\n", child2[1]) ;
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				fprintf(stderr, "invalid expression! Invalid type sizes! - %s at line %d\n", "+ - * /", exp->line);
				exit(1);
			}
		}
		else
		{
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			fprintf(stderr, "invalid expression! Invalid types! - %s at line %d\n", "+ - * /", exp->line);
			exit(1);
		}
	}

	else if (exp->type == AST_GREATER || exp->type == AST_LESS || exp->type == AST_GREATER_EQUAL 
		 || exp->type == AST_LESS_EQUAL || exp->type == AST_EQUAL || exp->type == AST_NOT_EQUAL)
	{
		if(exp->firstChild->type == AST_ID && exp->firstChild->size > 0)  // se for vetor, pega o proximo dps do vetor
		{
			int cont = 0 ;
			AST* begNext = exp->firstChild->nextSibling ;
			while(cont < exp->firstChild->size)
			{
				begNext = begNext->nextSibling ;
				cont++ ;
			}

			//child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child1[0] = exp->firstChild->nextSibling->type ;
			child1[1] = exp->size ;
			child2 = Symbols_visitExpression(st, begNext) ;
		}
		else
		{
			child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child2 = Symbols_visitExpression(st, exp->lastChild) ;
		}

		if(((child1[0] == AST_NUMINT) || (child1[0] == AST_CHAR)) && ((child2[0] == AST_NUMINT) || (child2[0] == AST_CHAR)))
		{
			if(child1[1] == child2[1])
			{
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0, exp->size);
			}
			else
			{
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				fprintf(stderr, "invalid comparison expression! Invalid type sizes! - %s at line %d\n", "comparison", exp->line);
				exit(1);
			}
		}
		else
		{
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			fprintf(stderr, "invalid comparison expression! - %s at line %d\n", "comparison", exp->line);
			exit(1);
		}
	}

	else if (exp->type == AST_AND || exp->type == AST_OR)
	{
		if(exp->firstChild->type == AST_ID && exp->firstChild->size > 0)  // se for vetor, pega o proximo dps do vetor
		{
			int cont = 0 ;
			AST* begNext = exp->firstChild->nextSibling ;
			while(cont < exp->firstChild->size)
			{
				begNext = begNext->nextSibling ;
				cont++ ;
			}

			//child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child1[0] = exp->firstChild->nextSibling->type ;
			child1[1] = exp->size ;
			child2 = Symbols_visitExpression(st, begNext) ;
		}
		else
		{
			child1 = Symbols_visitExpression(st, exp->firstChild) ;
			child2 = Symbols_visitExpression(st, exp->lastChild) ;
		}

		if(child1[0] == AST_BOOL && child2[0] == AST_BOOL)
		{
			if((child1[1] == child2[1]) && (child1[1] == 0))
			{
				fprintf(stderr, "ENTROU!!!\n") ;
				return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0, exp->size);
			}
			else
			{
				ret_expression[0]=-1 ;
				ret_expression[1]=-1 ;
				fprintf(stderr, "invalid and/or expression! Invalid type sizes! - %s at line %d\n", "and/or", exp->line);
				exit(1);
			}
		}

		else
		{
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			fprintf(stderr, "invalid and/or expression! - %s at line %d\n", "and/or", exp->line);
			exit(1);
		}
	}

	else if (exp->type == AST_NOT)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(child1[0] == AST_BOOL && child1[1] == 0)
		{
			return Symbols_setExpression (ret_expression, exp, SYM_BOOL, AST_BOOL, 0, exp->size);
		}

		else
		{
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			fprintf(stderr, "invalid \"not\" expression! - %s at line %d\n", "not", exp->line);
			exit(1);
		}
	}

	else if (exp->type == AST_NEG)
	{
		child1 = Symbols_visitExpression(st, exp->firstChild) ;

		if(((child1[0] == AST_NUMINT) && (child1[1] == 0)) || ((child1[0] == AST_CHAR) && (child1[1] == 0)))
		{
			return Symbols_setExpression (ret_expression, exp, SYM_INT, AST_NUMINT, 0, exp->size);
		}

		else
		{
			ret_expression[0]=-1 ;
			ret_expression[1]=-1 ;
			fprintf(stderr, "invalid - expression! - %s at line %d\n", "neg", exp->line);
			exit(1);
		}
	}

	ret_expression[0]=-1 ;
	ret_expression[1]=-1 ;
	fprintf(stderr, "invalid expression! - %s at line %d\n", "exp", exp->line);
	exit(1);
}

static bool Symbols_visitConditional(SymbolTable* st, AST* node) 
{
	int* exp_type = (int*)malloc(3*sizeof(int)) ;
	fprintf(stderr, "visit exp \n") ;
	exp_type  = Symbols_visitExpression(st, node->firstChild) ;

	AST* child = node->firstChild->nextSibling;

	if (exp_type[0] != AST_BOOL)
		return fail("condition expression is not a boolean value!", "?!?!", node);
	else if (exp_type[1] != 0)
		return fail("condition expression is a boolean array!", "?!?!", node);

	node->symbol_type == SYM_BOOL ;
	node->size = exp_type[1] ;

	while(child != NULL)
	{
		bool ok ;
		if (child->type == AST_BLOCK)
		{
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_BLOCK_ELSE)
		{
			ok = Symbols_visitBlockElse(st, child);
		}
		else if (child->type == AST_END)
		{
			ok = true;   //VER O QUE FAZER COM O END!
		}
		else
			ok = fail("Internal compiler error! - conditional\n", "!?!?", node);

		child = child->nextSibling ;
	
		if(!ok)
			return false ;
	}

	return true ;
}

static bool Symbols_visitIf(SymbolTable* st, AST* _if) 
{
	fprintf(stderr, "visit if\n") ;
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
	int* exp_type = (int*)malloc(3*sizeof(int)) ;

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
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_BLOCK_ELSE)
		{
			ok = Symbols_visitBlockElse(st, child);
		}
		else if (child->type == AST_LOOP)
		{
			ok = true;   //VERO QUE FAZER COM O LOOP
		}
		else
			ok = fail("Internal compiler error! - while", "!?!?", _while);

		child = child->nextSibling ;

		if(!ok)
			return false ;
	}

	return true ;
}



static bool Symbols_setReturn(SymbolTable* st, AST* _return, int symbol_type, int* exp_result)
{
	_return->symbol_type = symbol_type ;
	_return->size = exp_result[1] ;
	Symbol* existing = SymbolTable_get(st, "@ret", symbol_table_scope);

	if(existing)
	{
		if(existing->type != _return->symbol_type)
			return fail("invalid return expression!", "return", _return);

		if(existing->size != _return->size)
			return fail("invalid return expression; different sizes!", "return", _return);
	}
	else
		return fail("expression has no return!", "return", _return);
}

static bool Symbols_visitReturn(SymbolTable* st, AST* _return) 
{

//APAGAR @RET DPS DE USAR!
	int* exp_type ;

	if( _return->firstChild != NULL)
	{
		exp_type  = Symbols_visitExpression(st, _return->firstChild) ;

		if (exp_type[0] == -1)
			return fail("invalid return expression!", "return", _return);
		else if (exp_type[0] == AST_NUMINT)
		{
			Symbols_setReturn(st, _return, SYM_INT, exp_type) ;
		}
		else if (exp_type[0] == AST_CHAR)
		{
			Symbols_setReturn(st, _return, SYM_CHAR, exp_type) ;
		}
		else if (exp_type[0] == AST_BOOL)
		{
			Symbols_setReturn(st, _return, SYM_BOOL, exp_type) ;
		}
		else
		{
			if(_return->firstChild->symbol_type == SYM_INT)
				Symbols_setReturn(st, _return, SYM_INT, exp_type) ;

			else if(_return->firstChild->symbol_type == SYM_CHAR)
			{
				Symbols_setReturn(st, _return, SYM_INT, exp_type) ;
			}

			else if(_return->firstChild->symbol_type == SYM_BOOL)
				Symbols_setReturn(st, _return, SYM_INT, exp_type) ;
			else
				return fail("Internal compiler error! - return", "!?!?", _return);	
		}
	}
	
	return true ;
}

static bool Symbols_visitNew(SymbolTable* st, AST* _new) 
{
	int* exp_type ;

	exp_type  = Symbols_visitExpression(st, _new->firstChild) ;

	if (exp_type[0] != AST_NUMINT) 
	{
		if(exp_type[0] != AST_CHAR)
			return fail("invalid \"new\" expression!", "new", _new);
	}

	if(_new->firstChild->type == AST_NUMINT)
	{
		_new->symbol_type = SYM_INT ;
		_new->size = _new->lastChild->size+1 ;
	}
	else if(_new->firstChild->type == AST_CHAR)
	{
		_new->symbol_type = SYM_CHAR ;
		_new->size = _new->lastChild->size+1 ;
	}
	else if(_new->firstChild->type == AST_STRING)
	{
		_new->symbol_type = SYM_CHAR ;
		_new->size = 1 ;
	}
	else if(_new->firstChild->type == AST_BOOL)
	{
		_new->symbol_type = SYM_BOOL ;
		_new->size = _new->lastChild->size+1 ;
	}
	else
	{
		return fail("Internal compiler error! - new", "!?!?", _new);
	}	

	return true ;
}

static bool Symbols_visitCall(SymbolTable* st, AST* call) 
{
	const char* name = call->firstChild->stringVal;
	printf("name!!!! %s\n", name) ;
  	Symbol* existing = SymbolTable_getCall(st, name, symbol_table_scope);
	AST* child =  call->firstChild->nextSibling;
	int cont_param = 0;

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
				Symbol* existing_id = SymbolTable_get(st, param_name, symbol_table_scope);

				if(existing_id)
				{
					if (existing_id->type == SYM_FUN) 
         					return fail("is a function!", name, call);
					else
					{
						if (existing_id->type == SYM_INT)
						{
							if (existing->fun_param[cont_param][0] == AST_INT && 
							existing->fun_param[cont_param][1] == existing_id->size)
							{
								cont_param++ ;
							}
							else
								return fail("invalid parameter!1", param_name, child);
						}
						else if (existing_id->type == SYM_CHAR)
						{
							if (existing->fun_param[cont_param][0] == AST_CHAR && 
							existing->fun_param[cont_param][1] == existing_id->size)
							{
								cont_param++ ;
							}
							else
								return fail("invalid parameter!2", param_name, child);
						}
						else if (existing_id->type == SYM_BOOL)
						{
							if (existing->fun_param[cont_param][0] == AST_BOOL && 
							existing->fun_param[cont_param][1] == existing_id->size)
							{
								cont_param++ ;
							}
							else
								return fail("invalid parameter!3", param_name, child);
						}
						else
							return fail("invalid parameter!4", param_name, child);
					}	
				}
				else
					return fail("undeclared id as parameter!", param_name, child);
			}
			else if (child->type == AST_NUMINT)
			{
				if (existing->fun_param[cont_param][0] == child->type && existing->fun_param[cont_param][1] == child->size)
				{
					cont_param++ ;
				}
				else
					return fail("parameter has invalid type!", name, call);
			}
			else if (child->type == AST_CHAR)
			{
				if (existing->fun_param[cont_param][0] == child->type && existing->fun_param[cont_param][1] == child->size)
				{
					cont_param++ ;
				}
				else
					return fail("parameter has invalid type!", name, call);
			}
			else if (child->type == AST_BOOL)
			{
				if (existing->fun_param[cont_param][0] == child->type && existing->fun_param[cont_param][1] == child->size)
				{
					cont_param++ ;
				}
				else
					return fail("parameter has invalid type!", name, call);
			}
			else
			{
				return fail("Internal compiler error! - call", "!?!?", call);
			}
			child = child->nextSibling;
		}

		call->symbol_type = SYM_FUN ;
      		assert(existing->type == SYM_FUN);

		printf("CONT PARAM %d\n", existing->fun_param[cont_param][1]) ;
		if (existing->fun_param[cont_param][1] != -1)
			return fail("missing parameters!", name, call);

      		return true;
   	}
   	return fail("undeclared function!", name, call);
}

static int Symbols_Module(int val1, int val2)
{
	int ans ;
	ans = val1 - val2 ;

	if(ans < 0)
		ans*= -1 ;

	return ans ;
}


static bool Symbols_visitAssign(SymbolTable* st, AST* assign) 
{
	const char* name = assign->firstChild->stringVal;
	int valExistingAssign = 0 ;
   	Symbol* existing = SymbolTable_get(st, name, symbol_table_scope);
	int* assign_type ;
	AST* assignVector ;

	assign_type = Symbols_visitExpression(st, assign->lastChild);

	assignVector = assign->firstChild->nextSibling ;
	while(assignVector != NULL)
	{
		if(assignVector->type == AST_ID)
		{
			const char* nameAssign = assignVector->stringVal ;
			Symbol* existingAssign = SymbolTable_get(st, nameAssign, symbol_table_scope);
			valExistingAssign = existingAssign->size ;
			break ;
		}
		assignVector = assignVector->nextSibling ;
	}

	if(okGlobal == false)
		return false ;

   	if (existing) 
	{
      		if (existing->type == SYM_FUN) 
         		return fail("is a function!", name, assign);

		else if (existing->type == SYM_INT)
		{
			if ((assign_type[0] == AST_NUMINT) || (assign_type[0] == AST_CHAR) || (assign_type[0] == AST_NEW))
			{
				if((Symbols_Module(assign_type[1], valExistingAssign))==
										(Symbols_Module(existing->size, assign->firstChild->size)))
				{
					assign->symbol_type = SYM_INT ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_INT ;
					assign->lastChild->size = assign_type[1] ;
					assign->intVal = assign_type[2] ;
					return true;
				}
				else
				{
					printf("assign size: %d\n", assign_type[1]);
					printf("valExistingAssign: %d\n", valExistingAssign);
					printf("existing size: %d\n", existing->size);
					printf("firstChild size: %d\n", assign->firstChild->size);
					return fail("assigned wrong size value to an int variable!", name, assign);
				}
			}
			else
				return fail("assigned invalid value to an int variable!", name, assign);
		}
		
		else if (existing->type == SYM_BOOL)
		{
			if (assign_type[0] == AST_BOOL || (assign_type[0] == AST_NEW))
			{
				if((Symbols_Module(assign_type[1], valExistingAssign))==
										(Symbols_Module(existing->size, assign->firstChild->size)))
				{
					assign->symbol_type = SYM_BOOL ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_BOOL ;
					assign->lastChild->size = assign_type[1] ;
					assign->intVal = assign_type[2] ;
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
			if (assign_type[0] == AST_CHAR || (assign_type[0] == AST_NEW))
			{
				if((Symbols_Module(assign_type[1], valExistingAssign))==
										(Symbols_Module(existing->size, assign->firstChild->size)))
				{
					assign->symbol_type = SYM_CHAR ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_CHAR ;
					assign->lastChild->size = assign_type[1] ;
					assign->intVal = assign_type[2] ;
					return true;
				}
				else
					return fail("assigned wrong size value to char variable!1", name, assign);
			}
			else if (assign_type[0] == AST_NUMINT || (assign_type[0] == AST_NEW))
			{
				if((Symbols_Module(assign_type[1], valExistingAssign))==
										(Symbols_Module(existing->size, assign->firstChild->size)))
				{
					assign->symbol_type = SYM_CHAR ;
					assign->size = assign_type[1] ;			
					assign->lastChild->symbol_type = SYM_CHAR ;
					assign->lastChild->size = assign_type[1] ;

					if(assign_type[2] > 127 && assign_type[2] < -128)
						assign->intVal = (assign_type[2] >> 16) ;
					else
						assign->intVal = assign_type[2] ;
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
   	Symbol* existing = SymbolTable_get(st, name, symbol_table_scope);		
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
		declvar->symbol_type = SYM_INT ;
		declvar->firstChild->symbol_type = SYM_INT ;
	}

	else if (declvar->firstChild->nextSibling->type == AST_BOOL)
	{
		declvar->symbol_type = SYM_BOOL ;
		declvar->firstChild->symbol_type = SYM_BOOL ;
	}

	else if (declvar->firstChild->nextSibling->type == AST_CHAR)
	{
		declvar->symbol_type = SYM_CHAR ;
		declvar->firstChild->symbol_type = SYM_CHAR ;
	}
	
	else if (declvar->firstChild->nextSibling->type == AST_STRING)
	{
		declvar->symbol_type = SYM_CHAR ;
		declvar->firstChild->symbol_type = SYM_CHAR ;
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
			return fail("Internal compiler error - parameter/global", "!?!?", node);
		}
	}
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
				ok = Symbols_visitIf(st, child);
			}
        		else if (child->type == AST_WHILE)
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
				returned = 1;
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
	int qtd_params = 0, cont = 0;
	int armazena_params [50][2] ;
	int ret[2] ; /* ret_tipo[0] = tipo de retorno ; ret_tipo[1] == tamanho do array */
	returned = 0;
	has_return = 0 ;

	Symbol* existing = SymbolTable_get(st, name, symbol_table_scope);
	if (existing) 
	{
      	   	return fail("redeclared function!\n", name, function);
	}

	ret[0] = -1 ;
	ret[1] = -1 ;

	while (child != NULL)
	{
		bool ok;   	
      
		if (child->type == AST_PARAM)
		{
			ok = Symbols_visitParameter(st, child);
			armazena_params[qtd_params][0] = child->lastChild->type ; 
			armazena_params[qtd_params][1] = child->lastChild->size ;

			qtd_params++ ;
		}
		else if (child->type == AST_BLOCK)
		{
			ok = Symbols_visitBlock(st, child);
		}
		else if (child->type == AST_INT)
		{
			ret[0] = SYM_INT ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_INT, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
			has_return = 1 ;
		}
		else if (child->type == AST_CHAR)
		{
			ret[0] = SYM_CHAR ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_CHAR, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
			has_return = 1 ;
		}
		else if (child->type == AST_STRING)
		{
			ret[0] = SYM_CHAR ;
			ret[1] = 1 ;
			SymbolTable_add(st, "@ret", SYM_CHAR, child->line, 1,  symbol_table_scope, 0, 0, ret);
			ok = true ;
			has_return = 1 ;
		}
		else if (child->type == AST_BOOL)
		{
			ret[0] = SYM_BOOL ;
			ret[1] = child->size ;
			SymbolTable_add(st, "@ret", SYM_BOOL, child->line, child->size,  symbol_table_scope, 0, 0, ret);
			ok = true ;
			has_return = 1 ;
		}
		else 
	        	fail("Internal compiler error! - function", "!?!?", function);
      		
      		if (!ok) 
	        	return false;

		 child = child->nextSibling ;
	        
   	}

	if (returned == 0 && ret[0] != -1)
		fail("missing return", "!?!?", function);

	printf("nome da funcao a ser inserida: %s\n", name) ;
	SymbolTable_add(st, name, SYM_FUN, function->line, function->size, symbol_table_scope, qtd_params, armazena_params, ret);
	return true;
}

bool Symbols_annotate(AST* program) 
{
	SymbolTable* st = SymbolTable_new();
	AST* child = program->firstChild;

	symbol_table_scope = -1;

	while(child != NULL)
	{
		if (child->type == AST_FUN)
		{
			symbol_table_scope++;
        		bool ok = Symbols_visitFunction(st, child);

        		if (!ok) 
			{
				SymbolTable_print(st);
        			return false;
      			}
			SymbolTable_print(st);
		}
		else if (child->type == AST_GLOBAL)
		{
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

	SymbolTable_print(st);
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


