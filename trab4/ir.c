#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ir.h"
#include "micro-0.tab.h"

void IR_startFunction(IR* ir, const char* name) 
{
   // marca na estrutura IR que estamos gerando uma func nova
}

char* IR_newTemp(IR* ir) {
   char* temp = malloc(20);
   snprintf(temp, 20, "$t%d", ir->temps);
   ir->temps++;
   return temp;
}

void IR_genDeclVar(IR* ir, AST* entry) 
{
	printf(" %s = 0\n", entry->firstChild->stringVal);
}

void IR_genCall(IR* ir, AST* entry) 
{
	printf(" call %s\n", entry->firstChild->stringVal);
}

//NEW

char* IR_genExp(IR* ir, AST* exp) {
   switch (exp->type) {
      case AST_ADD: {
         char* temp = IR_newTemp(ir);
         char* e1 = IR_genExp(ir, exp->firstChild);
         char* e2 = IR_genExp(ir, exp->firstChild->nextSibling);
         printf(" %s = %s + %s\n", temp, e1, e2);
         return temp;
      }
      case LITNUM: {
         char* num = malloc(20);
         snprintf(num, 20, "%d", exp->intVal);
         return num;
      }
      case ID:
         return strdup(exp->stringVal);
      default:
         assert(0);
         return NULL;
   }
}

void IR_genAssign(IR* ir, AST* assign) 
{
   	const char* name = assign->firstChild->stringVal;
   	char* rval = IR_genExp(ir, assign->firstChild->nextSibling);
   	printf(" %s = %s\n", name, rval);
   	free(rval);
}


void IR_genBlockElseEntry(IR* ir, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_ELSEIF:
        	 	IR_genElseIf(ir, entry);
         		return;
	      	case AST_ELSE:
        	 	IR_genElse(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
}

void IR_genBlockElse(IR* ir, AST* block_else)
{
   	//IR_startFunction(ir, function->stringVal);
	//printf("block_e %s()\n", block->stringVal);
   	for(AST* child = block->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockElseEntry(ir, child);
   	}
}

void IR_genBlockEntry(IR* ir, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_IF:
        	 	IR_genIf(ir, entry);
         		return;
	      	case AST_WHILE:
        	 	IR_genWhile(ir, entry);
         		return;
	      	case AST_CALL:
        	 	IR_genCall(ir, entry);
         		return;
	      	case AST_RET:
        	 	IR_genRet(ir, entry);
         		return;
	      	case AST_DECLVAR:
        	 	IR_genDeclVar(ir, entry);
         		return;
	      	case AST_ATRIB:
        	 	IR_genAssign(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
}

void IR_genBlock(IR* ir, AST* block)
{
   	//IR_startFunction(ir, function->stringVal);
	printf("block %s()\n", block->stringVal);
   	for(AST* child = block->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockEntry(ir, child);
   	}
}

void IR_genFunctionEntry(IR* ir, AST* entry) 
{
   	switch (entry->type) 
	{
	      	case AST_PARAM:
        	 	IR_genParam(ir, entry);
         		return;
      		case AST_BLOCK:
         		IR_genBlock(ir, entry);
         		return;
      		case AST_INT:
         		IR_genInt(ir, entry);
         		return;
      		case AST_CHAR:
         		IR_genChar(ir, entry);
         		return;
      		case AST_STRING:
         		IR_genString(ir, entry);
         		return;
      		case AST_BOOL:
         		IR_genBool(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;

   	/*switch (entry->type) 
	{
	      	case AST_DECLVAR:
        	 	IR_genDeclVar(ir, entry);
         		return;
      		case AST_ASSIGN:
         		IR_genAssign(ir, entry);
         		return;
      		case AST_CALL:
         		IR_genCall(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
   	}*/
}

void IR_genFunction(IR* ir, AST* function) 
{
   	IR_startFunction(ir, function->stringVal);
	printf("fun %s()\n", function->stringVal);
   	for(AST* child = function->firstChild; child; child = child->nextSibling) 
	{
      		IR_genFunctionEntry(ir, child);
   	}
}

IR* IR_new() 
{
   	return (IR*) calloc(1, sizeof(IR));
}

IR* IR_gen(AST* program) 
{
   	IR* ir = IR_new();
   	for(AST* child = program->firstChild; child; child = child->nextSibling) 
	{
      		IR_genFunction(ir, child);
   	}
   	return ir;
}
