#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ir.h"
//#include "micro-0.tab.h"

static void IR_startFunction(IR* ir, const char* name) ;
static char* IR_newTemp(IR* ir)  ;
static void IR_genDeclVar(IR* ir, AST* entry) ;
static void IR_genCall(IR* ir, AST* entry) ;
static void IR_genParam(IR* ir, AST* entry) ;
static void IR_genRet(IR* ir, AST* entry) ;
static void IR_genInt(IR* ir, AST* entry) ;
static void IR_genChar(IR* ir, AST* entry) ;
static void IR_genBool(IR* ir, AST* entry) ;
static void IR_genString(IR* ir, AST* entry) ;
static char* IR_genExp(IR* ir, AST* exp) ;
static void IR_genAssign(IR* ir, AST* assign) ;
static void IR_genElseEntry(IR* ir, AST* entry) ;
static void IR_genElse(IR* ir, AST* _else) ;
static void IR_genIfEntry(IR* ir, AST* entry) ;
static void IR_genElseIf(IR* ir, AST* elseif) ;
static void IR_genIf(IR* ir, AST* _if) ;
static void IR_genWhileEntry(IR* ir, AST* entry) ;
static void IR_genWhile(IR* ir, AST* _while) ;
static void IR_genBlockElseEntry(IR* ir, AST* entry) ;
static void IR_genBlockElse(IR* ir, AST* block_else) ;
static void IR_genBlockEntry(IR* ir, AST* entry) ;
static void IR_genBlock(IR* ir, AST* block) ;
static void IR_genFunctionEntry(IR* ir, AST* entry) ;
static void IR_genFunction(IR* ir, AST* function) ;
static IR* IR_new() ;


static void IR_startFunction(IrTable* tab, const char* name) 
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

static NodeFunc* IR_newFunc(const char* name) 
{
	NodeFunc* func = (NodeFunc*)malloc(sizeof(NodeFunc)) ;
	func->firstCte = NULL ;
	func->lastCte = NULL ;
	func->nextFunc = NULL ;
	func->funcName = name ;
	return func ;
}

static NodeTable* IR_newNode(char* label, char* operand, char* op1, char* op2, char* op3) 
{
	NodeTable* node = (NodeTable*)malloc(sizeof(NodeTable)) ;
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

static IrTable* IR_newTable(IR* ir) 
{
	IrTable* new_table = (IrTable*)malloc(sizeof(IrTable)) ;
	IrTable->firstFunc = NULL ;
	IrTable->ir = ir ; 
}

static void IR_insert_operands(NodeFunc* func, const char* label, const char* operand, const char* op1, const char* op2, const char* op3) 
{
	NodeTable* node = IR_newNode(label, operand, op1, op2, op3) ; 
	if(func->firstCte == NULL)
	{
		func->firstCte = node ;
		func->lastCte = func->firstCte ;
	}
	else
	{
		func->lastCte->nextNode = node ;
		node->prevNode = func->lastCte ;
		func->lastNode = node ;
	}
}

static void IR_genDeclVar(IrTable* tab, AST* entry) 
{
	printf(" %s = 0\n", entry->firstChild->stringVal);
}

static void IR_genCall(IrTable* tab, AST* entry) 
{
	printf(" call %s\n", entry->firstChild->stringVal);
}

static void IR_genParam(IrTable* tab, AST* entry)
{
	printf(" %s,", entry->firstChild->stringVal);
}

static void IR_genRet(IrTable* tab, AST* entry)
{
	printf(" ret %s\n", entry->firstChild->stringVal);
}

static void IR_genInt(IrTable* tab, AST* entry)
{
	printf(" int ");
}

static void IR_genChar(IrTable* tab, AST* entry)
{
	printf(" char ");
}

static void IR_genBool(IrTable* tab, AST* entry)
{
	printf(" bool ");
}

static void IR_genString(IrTable* tab, AST* entry)
{
	printf(" string ");
}

//NEW

static char* IR_genExp(IR* ir, AST* exp) //FAZER OS OUTROS CASOS
{
	switch (exp->type) {
      		case AST_PLUS: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s + %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_MINUS: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s - %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_TIMES: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s * %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_DIVIDED: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s - %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_LESS: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s < %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_GREATER: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s > %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_GREATER_EQUAL: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s >= %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_LESS_EQUAL: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s <= %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_EQUAL: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s = %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_NOT_EQUAL: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s < %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_AND: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         		printf(" %s = %s and %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_OR: {
         		char* temp = IR_newTemp(ir);
         		char* e1 = IR_genExp(ir, exp->firstChild);
         		char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
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

static void IR_genAssign(IrTable* tab, AST* assign) 
{
   	const char* name = assign->firstChild->stringVal;
   	char* rval = IR_genExp(tab->ir, assign->firstChild->nextSibling);
   	printf(" %s = %s\n", name, rval);
   	free(rval);
}

static void IR_genElseEntry(IrTable* tab, AST* entry) 
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

static void IR_genElse(IrTable* tab, AST* _else)
{
   	//IR_startFunction(ir, function->stringVal);
	printf(" else\n");
	AST* child = NULL ;
   	for(child = _else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genElseEntry(tab, child);
   	}
}

static void IR_genIfEntry(IrTable* tab, AST* entry) 
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

static void IR_genElseIf(IrTable* tab, AST* elseif)
{
	char* temp = IR_genExp(tab, elseif->firstChild);
	char* label = IR_newLabel(tab) ;
	printf(" else if %s go to %s\n", temp, label);
	AST* child = elseif->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
      		IR_genIfEntry(tab, child);
   	}
	printf("%s\n", label);
}

static void IR_genIf(IrTable* tab, AST* _if)
{
	char* temp = IR_genExp(tab->ir, _if->firstChild);
	char* label = IR_newLabel(tab) ;
	printf(" if false %s go to %s\n", temp, label);
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


static void IR_genWhileEntry(IrTable* tab, AST* entry) 
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

static void IR_genWhile(IrTable* tab, AST* _while)
{
	char* temp = IR_genExp(tab->ir, _while->firstChild);
	char* label = IR_newLabel(tab) ;
	char* labelLoop = IR_newLabel(tab) ;
	static void IR_insert_operands(tab->lastNode, loopLabel, "if false", label, NULL) ;
	printf("%s:\n", labelLoop);
	printf(" if ! %s\n", temp);
	printf(" go to %s\n", label);
	AST* child = _while->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
      		IR_genWhileEntry(tab, child);
   	}
	printf(" go to %s\n", labelLoop);
	printf("%s\n", label);
}

static void IR_genBlockElseEntry(IrTable* tab, AST* entry) 
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

static void IR_genBlockElse(IrTable* tab, AST* block_else)
{
	AST* child = NULL ;
   	for(child = block_else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockElseEntry(tab, child);
   	}
}

static void IR_genBlockEntry(IrTable* tab, AST* entry) 
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

static void IR_genBlock(IrTable* tab, AST* block)
{
	AST* child = NULL ;
   	for(child = block->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockEntry(tab, child);
   	}
}

static void IR_genFunctionEntry(IrTable* tab, AST* entry) 
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

static void IR_genFunction(IrTable* tab, AST* function) 
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

IrTable* IR_gen(AST* program) 
{
   	IR* ir = IR_new();
	IrTable* tab = IR_newTable(ir) ;
	AST* child = NULL ;
   	for(child = program->firstChild; child; child = child->nextSibling) 
	{
      		IR_genFunction(table, child);
   	}
   	return tab;
}
