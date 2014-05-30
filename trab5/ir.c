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
static char* IR_genExp(OpTable* tab, AST* exp, char* temp, char* not) ;
static char* insertRightAssign (OpTable* tab, AST* id) ;
static void IR_genAssign(OpTable* tab, AST* assign) ;
static void IR_genElseEntry(OpTable* tab, AST* entry) ;
static void IR_genElse(OpTable* tab, AST* _else, char* labelFinal) ;
static void IR_genIfEntry(OpTable* tab, AST* entry, char* label, char* labelFinal) ;
static void IR_genElseIf(OpTable* tab, AST* elseif, char* labelFinal) ;
static void IR_genIf(OpTable* tab, AST* _if) ;
static void IR_genWhileEntry(OpTable* tab, AST* entry) ;
static void IR_genWhile(OpTable* tab, AST* _while) ;
static void IR_genBlockElseEntry(OpTable* tab, AST* entry, char* labelFinal) ;
static void IR_genBlockElse(OpTable* tab, AST* block_else, char* labelFinal) ;
static void IR_genBlockEntry(OpTable* tab, AST* entry) ;
static void IR_genBlock(OpTable* tab, AST* block) ;
static void IR_genFunctionEntry(OpTable* tab, AST* entry) ;
static void IR_genFunction(OpTable* tab, AST* function) ;
static void IR_genGlobal(OpTable* tab, AST* global) ;
static IR* IR_new() ;
static void IR_genEntry(OpTable* tab, AST* entry) ;


char* tempVec ;

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

	return node ;
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

	return node ;
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

static char* IR_getTemp(IR* ir) 
{
	char* temp = malloc(20);
	snprintf(temp, 20, "$t%d", ir->temps);
   	return temp;
}

static char* IR_newTemp(IR* ir) 
{
	char* temp = malloc(20);
	//printf(" CRIOU TEMP %d \n", ir->temps);
	snprintf(temp, 20, "$t%d", ir->temps);
   	ir->temps++;
   	return temp;
}

static char* IR_newString(IR* ir) 
{
	char* temp = malloc(20);
	snprintf(temp, 20, "$str%d", ir->strings);
   	ir->strings++;
   	return temp;
}

static char* IR_newLabel(IR* ir) 
{
	char* label = malloc(20);
	snprintf(label, 20, ".L%d", ir->labels);
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

static void IR_organizeParamCall(OpTable* tab) 
{
	NodeCte* firstParam = tab->lastNode->lastCte->prevNode ;
	NodeCte* aux ;
	int cont = 0 ;
	while(firstParam != NULL)
	{
		if(strcmp(firstParam->operand, "param") == 0)
		{
			if(firstParam->op3[0] == '0')
			{
				if(cont > 0)
					cont -- ;
				else
					break ;
			}
		}
		else if (strcmp(firstParam->operand, "call") == 0)	// um dos parametros é chamada de funcao
		{
			cont++ ;
		}
		firstParam = firstParam->prevNode ;
	}

	printf("first param %d\n!\n", firstParam) ;
	aux = firstParam ;
	NodeCte* aux2 ;
	while(aux != tab->lastNode->lastCte)
	{
		if(strcmp(aux->operand, "param") != 0)	//sobe o cte para antes do primeiro param
		{
			if(strcmp(aux->operand, "call") == 0) //se uma chamada é parametro
			{
				int cont = aux->op3 ;
				while(cont > 0)
				{
					aux2 = aux->prevNode ;
					NodeCte* beforeParam = firstParam->prevNode ;
					NodeCte* beforeAux2 = aux2->prevNode ;
					NodeCte* afterAux2 = aux ;

					beforeAux2->nextNode = afterAux2 ;
					afterAux2->prevNode = beforeAux2 ;

					aux2->prevNode = beforeParam ;
					aux2->nextNode = firstParam ;
					beforeParam->nextNode = aux2 ;
					firstParam->prevNode = aux2 ;
					cont-- ;	
				}
			}
			NodeCte* beforeParam = firstParam->prevNode ;
			NodeCte* beforeAux = aux->prevNode ;
			NodeCte* afterAux = aux->nextNode ;

			beforeAux->nextNode = afterAux ;
			afterAux->prevNode = beforeAux ;

			aux->prevNode = beforeParam ;
			aux->nextNode = firstParam ;
			beforeParam->nextNode = aux ;
			firstParam->prevNode = aux ;			
		}

		aux = aux->nextNode ;
	}

}

static void IR_insertParamCall(OpTable* tab, AST* param, int *cont) 
{
	if(param != NULL)
	{
		char* temp ;
		char* contString = malloc(3) ;
		IR_insertParamCall(tab, param->nextSibling, cont) ;
		char* lstParams = malloc (50) ;
		temp = IR_genExp(tab, param, NULL, NULL) ;
		snprintf(lstParams, 50, "param %s ", temp);
		snprintf(contString, 3, "%d ", *cont);
		IR_insert_operands(tab->lastNode, NULL, "param", lstParams, NULL, contString) ;
		printf("COOOOONT %d\n", *cont) ;
		printf("tab->lastNode->lastCte->op3 %s\n", tab->lastNode->lastCte->op3) ;
		(*cont)++ ;
	}

}

static void IR_genCall(OpTable* tab, AST* entry) 
{
	AST* param = entry->firstChild->nextSibling ;

	int cont = 0;
	IR_insertParamCall(tab, param, &cont) ;

	//printf(" call %s\n", entry->firstChild->stringVal);

	//strcpy(final, listParams) ;
	IR_insert_operands(tab->lastNode, NULL, "call", entry->firstChild->stringVal, NULL, cont) ;

	IR_organizeParamCall(tab) ;
}

static void IR_genParam(OpTable* tab, AST* entry)
{
	printf(" %s,", entry->firstChild->stringVal);
	tab->lastNode->params[tab->lastNode->numParams] = entry->firstChild->stringVal ;
	tab->lastNode->numParams++ ;
}

static void IR_genRet(OpTable* tab, AST* entry)
{
	char* temp ;
	if(entry->firstChild != NULL)
		if(entry->firstChild->stringVal != NULL)   //se retorna uma variavel
			IR_insert_operands(tab->lastNode, NULL, "ret", entry->firstChild->stringVal, NULL, NULL) ;
		else	//se retorna um numero
		{
			temp = IR_genExp(tab, entry->firstChild, NULL, NULL);
			IR_insert_operands(tab->lastNode, NULL, "ret", temp, NULL, NULL) ;
		}
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

static char* IR_insertAnd(OpTable* tab, AST* exp, char* operand, char* temp, char* not)
{
        char* e1 = IR_genExp(tab, exp->firstChild, NULL, not);
       printf(" achou e1 %s\n", e1);

	//IR_insert_operands(tab->lastNode, NULL, operand, strdup(temp), e1, e2) ;

	return e1 ;
}

static char* IR_insertExp(OpTable* tab, AST* exp, char* operand, char* temp, char* not)
{
	char* e1 = NULL ;
	char* e2 = NULL ;
	if(exp->firstChild->type == AST_ID && exp->firstChild->size > 0)
	{
		printf("aQUIIIIIIII\n") ;
		printf("var: %s\n", exp->firstChild->stringVal) ;
		int cont = 0 ;
		AST * next = exp->firstChild->nextSibling ;
		while(cont < exp->firstChild->size)
		{
			next = next->nextSibling ;
			cont++ ;
		}
		printf("temp: %s\n", temp) ;
		e1 = IR_genExp(tab, exp->firstChild, NULL, not);
		if( e1 == NULL)
			e1 = tempVec ;
		printf("next: %d\n", next->intVal) ;
        	e2 = IR_genExp(tab, next, NULL, not);
	}
	else
	{
        	e1 = IR_genExp(tab, exp->firstChild, NULL, not);
        	e2 = IR_genExp(tab, exp->firstChild->nextSibling, NULL, not);
	}

	IR_insert_operands(tab->lastNode, NULL, operand, strdup(temp), e1, e2) ;

	return temp ;
}



static char* IR_insertExpNot(OpTable* tab, AST* exp, char* temp)
{
        char* e1 = IR_genExp(tab, exp->firstChild, NULL, "not");
	printf(" achou e1 %s\n", e1);

	//IR_insert_operands(tab->lastNode, NULL, "not", strdup(temp), e1, NULL) ;

	return temp ;
}

static char* IR_genExp(OpTable* tab, AST* exp, char* var, char* not) //FAZER OS OUTROS CASOS
{
	char* temp = NULL;

	if((exp->type != AST_NUMINT) && (exp->type != AST_CHAR) && (exp->type != AST_STRING) && (exp->type != AST_BOOL) &&
	(exp->type != AST_TRUE) && (exp->type != AST_FALSE) && (exp->type != AST_LITERAL_STRING) && (exp->type != AST_NOT) &&
	(exp->type != AST_AND) && (exp->type != AST_NEG) && (exp->type != AST_NEW) && (exp->type != AST_ID))
	{
		if(var == NULL)
		{
    			temp = IR_newTemp(tab->ir);
		}
		else
		{
			temp = malloc(20) ;
			strcpy(temp, var);
		}
	}
	else if ((exp->type == AST_NOT) && (exp->firstChild->type != AST_TRUE) && (exp->firstChild->type != AST_TRUE))
	{
		if(var == NULL)
		{
    			temp = IR_getTemp(tab->ir);
		}
		else
		{
			temp = malloc(20) ;
			strcpy(temp, var);
		}
	}

	switch (exp->type) {
      		case AST_PLUS: {
			return IR_insertExp(tab, exp, "+", temp, not) ;
      		}
		case AST_MINUS: {
			return IR_insertExp(tab, exp, "-", temp, not) ;
      		}
		case AST_TIMES: {
			return IR_insertExp(tab, exp, "*", temp, not) ;
      		}
		case AST_DIVIDED: {
			return IR_insertExp(tab, exp, "/", temp, not) ;
      		}
		case AST_LESS: {
			if(not == NULL) 
				return IR_insertExp(tab, exp, "<", temp, not) ;
			else 
				return IR_insertExp(tab, exp, ">=", temp, not) ;
      		}
		case AST_GREATER: {
			if(not == NULL) 
				return IR_insertExp(tab, exp, ">", temp, not) ;
			else 
				return IR_insertExp(tab, exp, "<=", temp, not) ;
      		}
		case AST_GREATER_EQUAL: {
			if(not == NULL) 
				return IR_insertExp(tab, exp, ">=", temp, not) ;
			else 
				return IR_insertExp(tab, exp, "<", temp, not) ;
      		}
		case AST_LESS_EQUAL: {
			if(not == NULL) 
				return IR_insertExp(tab, exp, "<=", temp, not) ;
			else 
				return IR_insertExp(tab, exp, ">", temp, not) ;
      		}
		case AST_EQUAL: {
			if(not == NULL) 
				return IR_insertExp(tab, exp, "==", temp, not) ;
			else 
				return IR_insertExp(tab, exp, "!=", temp, not) ;
      		}
		case AST_NOT_EQUAL: {
			if(not == NULL) 

				return IR_insertExp(tab, exp, "!=", temp, not) ;
			else 
				return IR_insertExp(tab, exp, "==", temp, not) ;
      		}
		/*case AST_AND: {
			return IR_insertAnd(tab, exp, "and", temp, not) ;
      		}
		case AST_OR: {
         		char* temp = IR_newTemp(tab->ir);
         		char* e1 = IR_genExp(tab, exp->firstChild, NULL, not);
         		char* e2 = IR_genExp(tab, exp->firstChild->nextSibling, NULL, not);
         		printf(" %s = %s or %s\n", temp, e1, e2);
         		return temp;
      		}      	*/	
		case AST_NEG: {
			char* negExp = malloc(20) ;
			temp = IR_newTemp(tab->ir);
			snprintf(negExp, 20, "-%d", exp->firstChild->intVal);
			IR_insert_operands(tab->lastNode, NULL, "=", temp, negExp, NULL) ;
			return temp ;
      		}
		case AST_NEW: {
			char* newExp = malloc(20) ;
			snprintf(newExp, 20, "new %d", exp->firstChild->intVal);
			return newExp ;
      		}
		case AST_NOT: {
			//printf(" NOT\n");
			if(exp->firstChild->type == AST_TRUE)
				return "0" ;
			else if (exp->firstChild->type == AST_FALSE)
				return "1" ;
         		return IR_insertExpNot(tab, exp, temp) ;
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
      		case AST_ID: {
			if(exp->size == 0)
         			return strdup(exp->stringVal);
			else
			{
				return insertRightAssign (tab, exp) ;
			}
		}
      		case AST_CALL: {
			IR_genCall(tab, exp) ;
			IR_insert_operands(tab->lastNode, NULL, "=", temp, "$ret", NULL) ;
			return temp ;
		}
      		default:
			printf("TIPOOOO: %d\n", exp->type) ;
         		assert(0);
         		return NULL;
   	}

}

static char* insertRightAssign (OpTable* tab, AST* id)
{
	tempVec = IR_newTemp(tab->ir) ;
	char* temp1 = malloc(20) ;
	strcpy(temp1, tempVec) ;
	char* temp = NULL ;
	char* nam = malloc(20) ;
	int cont = 0 ;
	char * aux = malloc(20) ;
	AST* indexes = id->nextSibling ;
	snprintf(nam, 20, "%s[%d]", id->stringVal, indexes->intVal);
	IR_insert_operands(tab->lastNode, NULL, "=", temp1, nam, NULL) ;
	indexes = indexes->nextSibling ;
	cont++ ;

	printf("teeeeeeeemp: %s\n", temp1) ;

	while(cont < id->size)
	{
		printf("entroooooooou\n") ;
		//int index = assign->firstChild->nextSibling->intVal ;
		char* aux2 = malloc(20) ;
		temp = IR_newTemp(tab->ir) ;
		int index = indexes->intVal ;
		snprintf(aux2, 20, "%s[%d]", temp1, index);
		strcat(aux, aux2) ;
		IR_insert_operands(tab->lastNode, NULL, "=", temp, aux, NULL) ;
		indexes = indexes->nextSibling ;
		temp1 = temp ;
		cont++ ;
	}

	//snprintf(indexName, 20, "%s", temp);	
	return temp ;
}

static void IR_genAssign(OpTable* tab, AST* assign) 
{
   	char* name = assign->firstChild->stringVal;
	bool assVector = false ;
	char* rval = NULL ;
	AST* idPos = NULL ;
	AST* lookForId = assign->firstChild->nextSibling ;  /* ve se a atribuicao é de vetor */
	while(lookForId != NULL)
	{
		if(lookForId->type == AST_ID)	//recebe variavel
		{
			idPos = lookForId ;
			assVector++ ;
		}
		lookForId = lookForId->nextSibling ;
	}

	if(assVector > 0 && idPos->size > 0)
	{
		rval = IR_genExp(tab, idPos, name, NULL);
	}
	else
	{
		rval = IR_genExp(tab, assign->lastChild, name, NULL);
	}

	if((assign->firstChild->nextSibling->type == AST_NUMINT) || (assign->firstChild->nextSibling->type == AST_CHAR) ||
		(assign->firstChild->nextSibling->type == AST_STRING) || (assign->firstChild->nextSibling->type == AST_BOOL) ||
		(assign->firstChild->nextSibling->type == AST_TRUE) || (assign->firstChild->nextSibling->type == AST_FALSE) ||
		(assign->firstChild->nextSibling->type == AST_NEG) || (assign->firstChild->nextSibling->type == AST_NEW) ||
		(assign->firstChild->nextSibling->type == AST_ID))
	{

		if(assign->firstChild->size > 0)   // a var eh vetor
		{
			int cont = 0 ;
			AST* indexes = assign->firstChild->nextSibling ;
			char* indexName = malloc(20) ;
			char* aux = malloc(20) ;
			strcpy(aux,"") ;

			if(assign->firstChild->size == 0)
			{
				while(cont < assign->firstChild->size)
				{
					//int index = assign->firstChild->nextSibling->intVal ;
					char* aux2 = malloc(20) ;
					int index = indexes->intVal ;
					snprintf(aux2, 20, "[%d]", index);
					strcat(aux, aux2) ;
					printf("AUX: %s\n", aux) ;
					indexes = indexes->nextSibling ;
					cont++ ;
				}	
				snprintf(indexName, 20, "%s%s", name, aux);
			}
			else
			{
				char* temp1 = IR_newTemp(tab->ir) ;
				char* temp = temp1 ;
				char* nam = malloc(20) ;
				snprintf(nam, 20, "%s[%d]", name, indexes->intVal);
				IR_insert_operands(tab->lastNode, NULL, "=", temp1, nam, NULL) ;
				indexes = indexes->nextSibling ;
				cont++ ;
				
				while(cont < assign->firstChild->size)
				{
					//int index = assign->firstChild->nextSibling->intVal ;
					char* aux2 = malloc(20) ;
					temp = IR_newTemp(tab->ir) ;
					int index = indexes->intVal ;
					snprintf(aux2, 20, "%s[%d]", temp1, index);
					strcat(aux, aux2) ;
					IR_insert_operands(tab->lastNode, NULL, "=", temp, aux, NULL) ;
					indexes = indexes->nextSibling ;
					temp1 = temp ;
					cont++ ;
				}

				snprintf(indexName, 20, "%s", temp);			
			}
		

			if((assign->symbol_type == SYM_CHAR && assign->firstChild->symbol_type == SYM_INT) ||
				(assign->lastChild->type == AST_TRUE) || (assign->lastChild->type == AST_FALSE))
			{
				AST* auxNew  = assign->firstChild ;
				int newSize = 0 ;
				while(auxNew != NULL)
				{
					if(auxNew->type = AST_NEW)
					{
						newSize = auxNew->size ;
					}
					auxNew = auxNew->nextSibling ;					
				}
				if(newSize == 1)
					IR_insert_operands(tab->lastNode, NULL, "=", name, rval, "byte") ;
				else
					IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
			}
			else
   				IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
		}


		else
		{
			if((assign->symbol_type == SYM_CHAR && assign->firstChild->symbol_type == SYM_INT) ||
				(assign->lastChild->type == AST_TRUE) || (assign->lastChild->type == AST_FALSE))
			{
				AST* auxNew  = assign->firstChild ;
				int newSize = 0 ;
				while(auxNew != NULL)
				{
					if(auxNew->type = AST_NEW)
					{
						newSize = auxNew->size ;
					}
					auxNew = auxNew->nextSibling ;					
				}
				if(newSize == 1)
					IR_insert_operands(tab->lastNode, NULL, "=", name, rval, "byte") ;
				else
					IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
			}
			else
   				IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
		}
	}
	else if(assign->firstChild->nextSibling->type == AST_LITERAL_STRING)
	{
		char* newStr = malloc(20) ;
		newStr = IR_newString(tab->ir) ;
		IR_insert_string_operands(tab->lastNode, NULL, "string", newStr, rval, NULL) ;
	}

	//insere cte
	//IR_insert_operands(tab->lastNode, NULL, "=", name, rval, NULL) ;
   	printf(" ----%s = %s\n", name, rval);
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

static void IR_genElse(OpTable* tab, AST* _else, char* labelFinal)
{
   	//IR_startFunction(ir, function->stringVal);
	printf(" else\n");
	AST* child = NULL ;
   	for(child = _else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genElseEntry(tab, child);
   	}
	IR_insert_operands(tab->lastNode, labelFinal, "none", NULL, NULL, NULL) ;
}

static void IR_genIfEntry(OpTable* tab, AST* entry, char* label, char* labelFinal) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
	      	case AST_BLOCK_ELSE:
			IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
        	 	IR_genBlockElse(tab, entry, labelFinal);
         		return;
	      	case AST_END:
        	 	//IR_genElse(ir, entry);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_checkNextElse(OpTable* tab, AST* elseif, char* labelFinal, char* temp, char* label)
{
	int blockelse = 0 ;
	// checa se vem um proximo els if ou else
	AST* childAux = elseif->firstChild ;
   	for(childAux = childAux->nextSibling; childAux; childAux = childAux->nextSibling) 
	{
		if(childAux->type == AST_BLOCK_ELSE)
			blockelse++ ;
	}
	
	// se vem um else ou else if
	if(blockelse > 0)
		IR_insert_operands(tab->lastNode, NULL, "else if false", temp, label, NULL) ;

	//senao
	else
		IR_insert_operands(tab->lastNode, NULL, "else if false", temp, labelFinal, NULL) ;
}

static void IR_genElseIf(OpTable* tab, AST* elseif, char* labelFinal)
{
	char* temp = NULL ;
	char* label = IR_newLabel(tab->ir) ;
	int blockelse = 0 ;

	if (elseif->firstChild->type == AST_AND)
	{
		temp = IR_genExp(tab, elseif->firstChild->firstChild, NULL, NULL);
		IR_checkNextElse(tab, elseif, labelFinal, temp, label) ;

		temp = IR_genExp(tab, elseif->firstChild->lastChild, NULL, NULL);
	}
	else
		temp = IR_genExp(tab, elseif->firstChild, NULL, NULL);

	printf(" else if %s go to %s\n", temp, label);
	
	// checa qual label colocar no iffalse goto do else if
	IR_checkNextElse(tab, elseif, labelFinal, temp, label) ;

	AST* child = elseif->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
		if(child->type == AST_BLOCK_ELSE)
		{
			IR_insert_operands(tab->lastNode, NULL, "goto", labelFinal, NULL, NULL) ;
		}
      		IR_genIfEntry(tab, child, label, labelFinal);
   	}
	printf("%s\n", label);
	//IR_insert_operands(tab->lastNode, label, "none", NULL, NULL, NULL) ;
}

/*static void insertAndExp (OpTable* tab, AST* exp, char* temp, char* label)
{ 
	printf("ENTROUUUUUU\n");
	if (exp->firstChild->type == AST_AND)
		insertAndExp (tab, exp->firstChild, temp, label) ;

	temp = IR_genExp(tab, exp->firstChild, NULL, NULL);
	IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;

	temp = IR_genExp(tab, exp->lastChild, NULL, NULL);

}*/

static void IR_genIf(OpTable* tab, AST* _if)
{
	char* temp = NULL ;
	char* label = IR_newLabel(tab->ir) ;
	char* labelFinal = NULL;
	AST* _ifAux = _if->firstChild;
	int blockelse = 0 ;
	char* labelOr = NULL ;

	
	if (_ifAux->type == AST_AND)
	{
		//insertAndExp (tab, _ifAux->firstChild, temp, label) ;
		temp = IR_genExp(tab, _if->firstChild->firstChild, NULL, NULL);
		IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;

		temp = IR_genExp(tab, _if->firstChild->lastChild, NULL, NULL);
	}
	else if (_ifAux->type == AST_OR)
	{
		temp = IR_genExp(tab, _if->firstChild->firstChild, NULL, NULL);
		IR_insert_operands(tab->lastNode, NULL, "if", temp, label, NULL) ;
		labelOr = malloc(20) ;
		strcpy(labelOr, label) ;
		temp = IR_genExp(tab, _if->firstChild->lastChild, NULL, NULL);
		label = IR_newLabel(tab->ir) ;
	}
	else
		temp = IR_genExp(tab, _if->firstChild, NULL, NULL);

	printf(" if false %s go to %s -----%p\n", temp, label, temp);

	IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;

	if (_ifAux->type == AST_OR)
	{
		IR_insert_operands(tab->lastNode, labelOr, "none", NULL, NULL, NULL) ;
	}

	AST* child = _if->firstChild ;
   	for(child = child->nextSibling; child; child = child->nextSibling) 
	{
		if(child->type == AST_BLOCK_ELSE)
		{
			labelFinal = IR_newLabel(tab->ir) ;
			IR_insert_operands(tab->lastNode, NULL, "goto", labelFinal, NULL, NULL) ;
			blockelse++ ;
			printf(" go to %s\n", label);			
		}
      		IR_genIfEntry(tab, child, label, labelFinal);
   	}
	
	IR_insert_operands(tab->lastNode, labelFinal, "none", NULL, NULL, NULL) ;

	if(blockelse == 0)
	{
		char* label2 = malloc(20) ;
		strcpy(label2, label) ;
		printf("inseriu LABEEEEEL %s\n", label);
		IR_insert_operands(tab->lastNode, label2, "none", NULL, NULL, NULL) ;
	}
}


static void IR_genWhileEntry(OpTable* tab, AST* entry) 
{
	switch (entry->type) 
	{
	      	case AST_BLOCK:
        	 	IR_genBlock(tab, entry);
         		return;
	      	case AST_BLOCK_ELSE:
        	 	IR_genBlockElse(tab, entry, NULL);
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
	char* temp = IR_genExp(tab, _while->firstChild, NULL, NULL);
	char* label = IR_newLabel(tab->ir) ;
	char* labelLoop = IR_newLabel(tab->ir) ;


	if((tab->lastNode->lastCte->op2 != 0) && (tab->lastNode->lastCte->op2 != 1))
	{
		tab->lastNode->lastCte->label = labelLoop ; 
		IR_insert_operands(tab->lastNode, NULL, "if false", temp, label, NULL) ;
	}
	else
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

static void IR_genBlockElseEntry(OpTable* tab, AST* entry, char* labelFinal) 
{
	switch (entry->type) 
	{
	      	case AST_ELSEIF:
        	 	IR_genElseIf(tab, entry, labelFinal);
         		return;
	      	case AST_ELSE:
        	 	IR_genElse(tab, entry, labelFinal);
         		return;
      		default:
         		assert(0);
         		return;
	}
}

static void IR_genBlockElse(OpTable* tab, AST* block_else, char* labelFinal)
{
	AST* child = NULL ;
   	for(child = block_else->firstChild; child; child = child->nextSibling) 
	{
      		IR_genBlockElseEntry(tab, child, labelFinal);
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
