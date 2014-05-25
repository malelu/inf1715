#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ir.h"
//#include "micro-0.tab.h"

static void IR_startFunction(OpTable* tab, char* name) ;
static void IR_startGlobal(OpTable* tab, char* varName) ;
static NodeFunc* IR_newGlobal(char* varName) ;
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
static char* IR_genExp(OpTable* tab, AST* exp, char* temp) ;
static void IR_genAssign(OpTable* tab, AST* assign) ;
static void IR_genElseEntry(OpTable* tab, AST* entry) ;
static void IR_genElse(OpTable* tab, AST* _else) ;
static void IR_genIfEntry(OpTable* tab, AST* entry, char* label) ;
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
static void IR_genGlobal(OpTable* tab, AST* global) ;
static IR* IR_new() ;
static void IR_genEntry(OpTable* tab, AST* entry) ;


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

static void IR_startGlobal(OpTable* tab, char* varName) 
{
	if(tab->firstNode == NULL)
	{
		tab->firstNode = IR_newGlobal(varName) ;
		tab->lastNode = tab->firstNode ; 
	}
   	else
	{
		tab->lastNode->nextFunc = IR_newGlobal(varName) ;
		tab->lastNode = tab->lastNode->nextFunc ;
	}
}

static NodeFunc* IR_newGlobal(char* varName) 
{
	int i ;
	NodeFunc* func = (NodeFunc*)malloc(sizeof(NodeFunc)) ;
	func->firstCte = NULL ;
	func->lastCte = NULL ;
	func->nextFunc = NULL ;
	func->global = varName ;
	func->funcName = NULL ;
   	func->firstStringCte = NULL;
	func->params = (char**)calloc(10, sizeof(char*)) ;
	for(i=0; i<10; i++)
	{
		func->params[i] = NULL ;
	}
	func->numParams = 0 ;
	return func ;
}

static NodeFunc* IR_newFunc(char* name) 
{
	int i ;
	NodeFunc* func = (NodeFunc*)malloc(sizeof(NodeFunc)) ;
	func->firstCte = NULL ;
	func->lastCte = NULL ;
	func->nextFunc = NULL ;
	func->global = NULL ;
	func->funcName = name ;
   	func->firstStringCte = NULL;
   	func->lastStringCte = NULL;
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

static StringCte* IR_newNodeString(char* label, char* operand, char* op1, char* op2, char* op3) 
{
	StringCte* node = (StringCte*)malloc(sizeof(StringCte)) ;
	node->nextNode = NULL ;
	node->prevNode = NULL ;
	node->label = label ;
	node->operand = operand ;
	node->op1 = op1 ;
	node->op2 = op2 ;
	node->op3 = op3 ;
}

/*static GlobalCte* IR_newNodeGlobal(char* label, char* operand, char* op1, char* op2, char* op3) 
{
	GlobalCte* node = (GlobalCte*)malloc(sizeof(GlobalCte)) ;
	node->nextNode = NULL ;
	node->prevNode = NULL ;
	node->label = label ;
	node->operand = operand ;
	node->op1 = op1 ;
	node->op2 = op2 ;
	node->op3 = op3 ;
}
*/
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

static void IR_insert_string_operands(NodeFunc* func, char* label, char* operand, char* op1, char* op2, char* op3) 
{
	StringCte* node = IR_newNodeString(label, operand, op1, op2, op3) ;

	if(func->firstStringCte == NULL)
	{
		func->firstStringCte = node ;
		func->lastStringCte = func->firstStringCte ;
	}
	else
	{
		func->lastStringCte->nextNode = node ;
		node->prevNode = func->lastStringCte ;
		func->lastStringCte = node ;

	}
}

static void IR_insert_operands(NodeFunc* func, char* label, char* operand, char* op1, char* op2, char* op3) 
{
	NodeCte* node ;
	if(func->firstCte == NULL)
	{
		node = IR_newNode(label, operand, op1, op2, op3) ; 
		func->firstCte = node ;
		func->lastCte = func->firstCte ;
	}
	else
	{
		if(func->lastCte->operand == "none")
		{
			func->lastCte->operand = operand ;
			func->lastCte->op1 = op1 ;
			func->lastCte->op2 = op2 ;
			func->lastCte->op3 = op3 ;			
		}

		/*else if (strcmp(operand, "string") == 0)
		{

			NodeCte* auxNode ;
			node = IR_newNode(label, operand, op1, op2, op3) ; 

			auxNode = func->firstCte ;

			while(strcmp(auxNode->operand, "string") == 0)
			{
				auxNode = auxNode->nextNode ;
			}
			if(auxNode = func->firstCte)
			{
				node->nextNode = func->firstCte ;
				func->firstCte->prevNode = node ;
				func->firstCte = node ;
			}
			else
			{
				auxNode->prevNode->nextNode = node ;
				node->nextNode = auxNode ;
			}
		}*/


		else
		{
			node = IR_newNode(label, operand, op1, op2, op3) ; 
			func->lastCte->nextNode = node ;
			node->prevNode = func->lastCte ;
			func->lastCte = node ;
		}
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
	if(entry->firstChild != NULL)
		IR_insert_operands(tab->lastNode, NULL, "ret", entry->firstChild->stringVal, NULL, NULL) ;
	else
		IR_insert_operands(tab->lastNode, NULL, "ret", NULL, NULL, NULL) ;
	//printf(" ret %s\n", entry->firstChild->stringVal);
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

static char* IR_insertExp(OpTable* tab, AST* exp, char* operand, char* temp)
{
        char* e1 = IR_genExp(tab, exp->firstChild, NULL);
        char* e2 = IR_genExp(tab, exp->firstChild->nextSibling, NULL);
//printf(" TEMP2 %s e1 %s e2 %s\n", temp2, e1, e2);

	IR_insert_operands(tab->lastNode, NULL, operand, strdup(temp), e1, e2) ;

	return temp ;
}

static char* IR_genExp(OpTable* tab, AST* exp, char* var) //FAZER OS OUTROS CASOS
{
	char* temp = NULL;
	
	if((exp->type != AST_NUMINT) && (exp->type != AST_CHAR) && (exp->type != AST_STRING) && (exp->type != AST_BOOL) &&
	(exp->type != AST_TRUE) && (exp->type != AST_FALSE) && (exp->type != AST_LITERAL_STRING))
	{
		if(var == NULL)
		{
    			temp = IR_newTemp(tab->ir);
printf(" TEMP: %s %p\n", temp, temp);
		}
		else
		{
			fprintf(stdout, "VAR: %s\n", var);
			temp = malloc(20) ;
			strcpy(temp, var);
		}
	}

	switch (exp->type) {
      		case AST_PLUS: {
			return IR_insertExp(tab, exp, "+", temp) ;
      		}
		case AST_MINUS: {
			return IR_insertExp(tab, exp, "-", temp) ;
      		}
		case AST_TIMES: {
			return IR_insertExp(tab, exp, "*", temp) ;
      		}
		case AST_DIVIDED: {
			return IR_insertExp(tab, exp, "/", temp) ;
      		}
		case AST_LESS: {
			return IR_insertExp(tab, exp, "<", temp) ;
      		}
		case AST_GREATER: {
			return IR_insertExp(tab, exp, ">", temp) ;
      		}
		case AST_GREATER_EQUAL: {
			return IR_insertExp(tab, exp, "GE", temp) ;
      		}
		case AST_LESS_EQUAL: {
			return IR_insertExp(tab, exp, "LE", temp) ;
      		}
		case AST_EQUAL: {
//TRATAR!
			return IR_insertExp(tab, exp, "=", temp) ;
      		}
		case AST_NOT_EQUAL: {
//TRATAR
			return IR_insertExp(tab, exp, "NE", temp) ;
      		}
		case AST_AND: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild, NULL);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling, NULL);
         		printf(" %s = %s and %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_OR: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild, NULL);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling, NULL);
         		printf(" %s = %s or %s\n", temp, e1, e2);
         		return temp;
      		}
		case AST_TRUE: {
         		return "1";
      		}
		case AST_FALSE: {
         		return "0";
      		}
      		case AST_NUMINT: {
         		char* num = malloc(20);
         		snprintf(num, 20, "%d", exp->intVal);
			printf(" NUM %s\n", num);
         		return num;
      		}
      		case AST_LITERAL_STRING: {
         		char* str = malloc(50);
         		snprintf(str, 50, "\"%s\"", exp->stringVal);
         		return str;
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
   	char* name = assign->firstChild->stringVal;
	char* rval = IR_genExp(tab, assign->firstChild->nextSibling, name);

	if((assign->firstChild->nextSibling->type == AST_NUMINT) || (assign->firstChild->nextSibling->type == AST_CHAR) ||
		(assign->firstChild->nextSibling->type == AST_STRING) || (assign->firstChild->nextSibling->type == AST_BOOL) ||
		(assign->firstChild->nextSibling->type == AST_TRUE) || (assign->firstChild->nextSibling->type == AST_FALSE))
	{
   		IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
	}
	else if(assign->firstChild->nextSibling->type == AST_LITERAL_STRING)
		IR_insert_string_operands(tab->lastNode, NULL, "string", name, rval, NULL) ;

	//insere cte
	//IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
   	printf(" ----%s = %s\n", name, rval);
   	//free(rval);
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

/*static void IR_genIfEntry(OpTable* tab, AST* entry) 
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
*/
static void IR_genIfEntry(OpTable* tab, AST* entry, char* label) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
	      	case AST_BLOCK_ELSE:
			IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
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
	char* temp = IR_genExp(tab, elseif->firstChild, NULL);
	char* label = IR_newLabel(tab->ir) ;
	printf(" else if %s go to %s\n", temp, label);
	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "else if false", temp, label, NULL) ;

	AST* child = elseif->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
      		IR_genIfEntry(tab, child, label);
   	}
	printf("%s\n", label);
	//IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
}

static void IR_genIf(OpTable* tab, AST* _if)
{
	char* temp = IR_genExp(tab, _if->firstChild, NULL);
	char* label = IR_newLabel(tab->ir) ;
	printf(" if false %s go to %s -----%p\n", temp, label, temp);

	//insere cte
	IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;

	AST* child = _if->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
		if(child->type == AST_BLOCK_ELSE)
		{
			printf(" go to %s\n", label);			
		}
      		IR_genIfEntry(tab, child, label);
   	}
	printf("%s\n", label);
	IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
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
	char* temp = IR_genExp(tab, _while->firstChild, NULL);
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
	printf("fun %s( \n", function->stringVal);
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

static void IR_genEntry(OpTable* tab, AST* entry) 
{
   	switch (entry->type) 
	{
	      	case AST_FUN:
        	 	IR_genFunction(tab, entry);
         		return;
      		case AST_GLOBAL:
         		IR_startGlobal(tab, entry->firstChild->stringVal);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

OpTable* IR_gen(AST* program) 
{
   	IR* ir = IR_new();
	OpTable* tab = IR_newTable(ir) ;
	AST* child = NULL ;
   	for(child = program->firstChild; child; child = child->nextSibling) 
	{
      		IR_genEntry(tab, child);
   	}
   	return tab;
}
