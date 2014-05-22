#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ir.h"
//#include "micro-0.tab.h"

static void IR_startFunction(OpTable* tab, char* name) ;
static NodeFunc* IR_newFunc(char* name) ;
static NodeCte* IR_newNode(char* label, char* operand, char* op1, char* op2, char* op3) ;
static char* IR_newTemp(IR* ir) ;
static char* IR_newLabel(IR* ir) ;
static OpTable* IR_newTable(IR* ir) ;
static void IR_insert_operands(NodeFunc* func, char* label, char* operand, char* op1, char* op2, char* op3) ;
static void IR_genDeclVar(OpTable* tab, AST* entry) ;
static void IR_genCall(OpTable* tab, AST* entry) ;
static void IR_genParam(OpTable* tab, AST* entry) ;
static void IR_genRet(OpTable* tab, AST* entry) ;
static void IR_genInt(OpTable* tab, AST* entry) ;
static void IR_genChar(OpTable* tab, AST* entry) ;
static void IR_genBool(OpTable* tab, AST* entry) ;
static void IR_genString(OpTable* tab, AST* entry) ;
static char* IR_genExp(OpTable* tab, AST* exp) ;
static void IR_genAssign(OpTable* tab, AST* assign) ;
static void IR_genElseEntry(OpTable* tab, AST* entry) ;
static void IR_genElse(OpTable* tab, AST* _else) ;
static void IR_genIfEntry(OpTable* tab, AST* entry) ;
static void IR_genElseIf(OpTable* tab, AST* elseif) ;
static void IR_genIf(OpTable* tab, AST* _if) ;
static void IR_genWhileEntry(OpTable* tab, AST* entry) ;
static void IR_genWhile(OpTable* tab, AST* _while) ;
static void IR_genBlockElseEntry(OpTable* tab, AST* entry) ;
static void IR_genBlockElse(OpTable* tab, AST* block_else) ;
static void IR_genBlockEntry(OpTable* tab, AST* entry) ;
static void IR_genBlock(OpTable* tab, AST* block) ;
static void IR_genFunctionEntry(OpTable* tab, AST* entry) ;
static void IR_genFunction(OpTable* tab, AST* function) ;
static IR* IR_new() ;


static void IR_startFunction(OpTable* tab, char* name) 
{
	if(tab->firstNode == NULL)
	{
		tab->firstNode = IR_newFunc(name) ;
		tab->lastNode = tab->firstNode ; 
	}
   	else
	{
		tab->lastNode->nextFunc = IR_newFunc(name) ;
		tab->lastNode = tab->lastNode->nextFunc ;
	}
}

static NodeFunc* IR_newFunc(char* name) 
{
	int i ;
	NodeFunc* func = (NodeFunc*)malloc(sizeof(NodeFunc)) ;
	func->firstCte = NULL ;
	func->lastCte = NULL ;
	func->nextFunc = NULL ;
	func->funcName = name ;
	func->params = (char**)calloc(10, sizeof(char*)) ;
	for(i=0; i<10; i++)
	{
		func->params[i] = NULL ;
	}
	func->numParams = 0 ;
	return func ;
}

static NodeCte* IR_newNode(char* label, char* operand, char* op1, char* op2, char* op3) 
{
	NodeCte* node = (NodeCte*)malloc(sizeof(NodeCte)) ;
	node->nextNode = NULL ;
	node->prevNode = NULL ;
	node->label = label ;
	node->operand = operand ;
	node->op1 = op1 ;
	node->op2 = op2 ;
	node->op3 = op3 ;
}

static char* IR_newTemp(IR* ir) 
{
	char* temp = malloc(20);
	snprintf(temp, 20, "$t%d", ir->temps);
   	ir->temps++;
   	return temp;
}

static char* IR_newLabel(IR* ir) 
{
	char* label = malloc(20);
	snprintf(label, 20, "L%d", ir->labels);
   	ir->labels++;
   	return label;
}

static OpTable* IR_newTable(IR* ir) 
{
	OpTable* new_table = (OpTable*)malloc(sizeof(OpTable)) ;
	new_table->firstNode = NULL ;
	new_table->lastNode = NULL ;
	new_table->ir = ir ; 
}

static void IR_insert_operands(NodeFunc* func, char* label, char* operand, char* op1, char* op2, char* op3) 
{
	NodeCte* node = IR_newNode(label, operand, op1, op2, op3) ; 
	if(func->firstCte == NULL)
	{
		func->firstCte = node ;
		func->lastCte = func->firstCte ;
	}
	else
	{
		func->lastCte->nextNode = node ;
		node->prevNode = func->lastCte ;
		func->lastCte = node ;
	}
}

static void IR_genDeclVar(OpTable* tab, AST* entry) 
{
	printf(" %s = 0\n", entry->firstChild->stringVal);
	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "declvar", entry->firstChild->stringVal, 0, NULL) ;
}

static void IR_genCall(OpTable* tab, AST* entry) 
{
	printf(" call %s\n", entry->firstChild->stringVal);
	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "call", entry->firstChild->stringVal, NULL, NULL) ;
}

static void IR_genParam(OpTable* tab, AST* entry)
{
	printf(" %s,", entry->firstChild->stringVal);
	tab->lastNode->params[tab->lastNode->numParams] = entry->firstChild->stringVal ;
	tab->lastNode->numParams++ ;
}

static void IR_genRet(OpTable* tab, AST* entry)
{
	printf(" ret %s\n", entry->firstChild->stringVal);
}

static void IR_genInt(OpTable* tab, AST* entry)
{
	printf(" int ");
}

static void IR_genChar(OpTable* tab, AST* entry)
{
	printf(" char ");
}

static void IR_genBool(OpTable* tab, AST* entry)
{
	printf(" bool ");
}

static void IR_genString(OpTable* tab, AST* entry)
{
	printf(" string ");
}

//NEW

static char* IR_genExp(OpTable* tab, AST* exp) //FAZER OS OUTROS CASOS
{
	switch (exp->type) {
      		case AST_PLUS: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "+", temp, e1, e2) ;
         		printf(" %s = %s + %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_MINUS: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "-", temp, e1, e2) ;
         		printf(" %s = %s - %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_TIMES: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "*", temp, e1, e2) ;
         		printf(" %s = %s * %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_DIVIDED: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "/", temp, e1, e2) ;
         		printf(" %s = %s - %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_LESS: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "<", temp, e1, e2) ;
         		printf(" %s = %s < %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_GREATER: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, ">", temp, e1, e2) ;
         		printf(" %s = %s > %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_GREATER_EQUAL: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, ">=", temp, e1, e2) ;
         		printf(" %s = %s >= %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_LESS_EQUAL: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "<=", temp, e1, e2) ;
         		printf(" %s = %s <= %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_EQUAL: {
//TRATAR!
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "=", temp, e1, e2) ;
         		printf(" %s = %s = %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_NOT_EQUAL: {
//TRATAR
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
			//insere cte
			IR_insert_operands(tab->lastNode, NULL, "<>", temp, e1, e2) ;
         		printf(" %s = %s < %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_AND: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
         		printf(" %s = %s and %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_OR: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling);
         		printf(" %s = %s or %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_TRUE: {
         		return "true";
      		}
		case AST_FALSE: {
         		return "false";
      		}
      		case AST_NUMINT: {
         		char* num = malloc(20);
         		snprintf(num, 20, "%d", exp->intVal);
         		return num;
      		}
      		case AST_ID:
         		return strdup(exp->stringVal);
      		default:
         		assert(0);
         		return NULL;
   	}
}

static void IR_genAssign(OpTable* tab, AST* assign) 
{
   	const char* name = assign->firstChild->stringVal;
   	char* rval = IR_genExp(tab, assign->firstChild->nextSibling);
   	printf(" %s = %s\n", name, rval);
   	free(rval);
}

static void IR_genElseEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genElse(OpTable* tab, AST* _else)
{
   	//IR_startFunction(ir, function->stringVal);
	printf(" else\n");
	AST* child = NULL ;
   	for(child = _else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genElseEntry(tab, child);
   	}
}

static void IR_genIfEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
	      	case AST_BLOCK_ELSE:
        	 	IR_genBlockElse(tab, entry);
         		return;
	      	case AST_END:
        	 	//IR_genElse(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genElseIf(OpTable* tab, AST* elseif)
{
	char* temp = IR_genExp(tab, elseif->firstChild);
	char* label = IR_newLabel(tab->ir) ;
	printf(" else if %s go to %s\n", temp, label);
	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "else if false", temp, label, NULL) ;

	AST* child = elseif->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
      		IR_genIfEntry(tab, child);
   	}
	printf("%s\n", label);
}

static void IR_genIf(OpTable* tab, AST* _if)
{
	char* temp = IR_genExp(tab, _if->firstChild);
	char* label = IR_newLabel(tab->ir) ;
	printf(" if false %s go to %s\n", temp, label);

	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;

	AST* child = _if->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
		if(child->type == AST_BLOCK_ELSE)
		{
			printf(" go to %s\n", label);			
		}
      		IR_genIfEntry(tab, child);
   	}
	printf("%s\n", label);
}


static void IR_genWhileEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
	      	case AST_BLOCK_ELSE:
        	 	IR_genBlockElse(tab, entry);
         		return;
	      	case AST_LOOP:
        	 	//IR_genElse(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genWhile(OpTable* tab, AST* _while)
{
	char* temp = IR_genExp(tab, _while->firstChild);
	char* label = IR_newLabel(tab->ir) ;
	char* labelLoop = IR_newLabel(tab->ir) ;

	//insere cte
	IR_insert_operands(tab->lastNode, labelLoop, "if false", temp, label, NULL) ;

	printf("%s:\n", labelLoop);
	printf(" if ! %s\n", temp);
	printf(" go to %s\n", label);

	AST* child = _while->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
      		IR_genWhileEntry(tab, child);
   	}

	printf(" go to %s\n", labelLoop);
	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "goto", labelLoop, NULL, NULL) ;
	IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
	printf("%s\n", label);
}

static void IR_genBlockElseEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_ELSEIF:
        	 	IR_genElseIf(tab, entry);
         		return;
	      	case AST_ELSE:
        	 	IR_genElse(tab, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genBlockElse(OpTable* tab, AST* block_else)
{
	AST* child = NULL ;
   	for(child = block_else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockElseEntry(tab, child);
   	}
}

static void IR_genBlockEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_IF:
        	 	IR_genIf(tab, entry);
         		return;
	      	case AST_WHILE:
        	 	IR_genWhile(tab, entry);
         		return;
	      	case AST_CALL:
        	 	IR_genCall(tab, entry);
         		return;
	      	case AST_RET:
        	 	IR_genRet(tab, entry);
         		return;
	      	case AST_DECLVAR:
        	 	IR_genDeclVar(tab, entry);
         		return;
	      	case AST_ATRIB:
        	 	IR_genAssign(tab, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genBlock(OpTable* tab, AST* block)
{
	AST* child = NULL ;
   	for(child = block->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockEntry(tab, child);
   	}
}

static void IR_genFunctionEntry(OpTable* tab, AST* entry) 
{
   	switch (entry->type) 
	{
	      	case AST_PARAM:
        	 	IR_genParam(tab, entry);
         		return;
      		case AST_BLOCK:
         		IR_genBlock(tab, entry);
         		return;
      		case AST_INT:
         		IR_genInt(tab, entry);
         		return;
      		case AST_CHAR:
         		IR_genChar(tab, entry);
         		return;
      		case AST_STRING:
         		IR_genString(tab, entry);
         		return;
      		case AST_BOOL:
         		IR_genBool(tab, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genFunction(OpTable* tab, AST* function) 
{
   	IR_startFunction(tab, function->stringVal);
	printf("fun %s( ", function->stringVal);
	AST* child = NULL ;
   	for(child = function->firstChild; child; child = child->nextSibling) 
	{
      		IR_genFunctionEntry(tab, child);
   	}
}

static IR* IR_new() 
{
   	return (IR*) calloc(1, sizeof(IR));
}

OpTable* IR_gen(AST* program) 
{
   	IR* ir = IR_new();
	OpTable* tab = IR_newTable(ir) ;
	AST* child = NULL ;
   	for(child = program->firstChild; child; child = child->nextSibling) 
	{
      		IR_genFunction(tab, child);
   	}
   	return tab;
}
