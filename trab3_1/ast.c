#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* AST_new (int node_type, int line)
{
	
	AST* node = (AST*) malloc(sizeof(AST)) ;
	//fprintf(stderr, "entrou\n");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = node_type ;
	node->intVal = 0 ;
	node->stringVal = NULL ;
	//fprintf(stderr, "saiu\n");
	//fprintf(stderr, "%d\n", node->line);
	//fprintf(stderr, "%d\n", node->type);

	return node ;
}

void AST_addChild(AST* parent_node, AST* node)
{
	//fprintf(stderr, "entrou2\n");
	if(node != NULL)
	{
		if(parent_node->firstChild == NULL)
		{
			parent_node->firstChild = (AST*) malloc(sizeof(AST)) ;
			parent_node->lastChild = (AST*) malloc(sizeof(AST)) ;	
			parent_node->firstChild = node ;
			parent_node->lastChild = node ;
		}
		else
		{	
			
			parent_node->lastChild->nextSibling = (AST*) malloc(sizeof(AST)) ;
			parent_node->lastChild->nextSibling = node ;
			node->prevSibling = (AST*) malloc(sizeof(AST)) ;		
			node->prevSibling = parent_node->lastChild ;
			parent_node->lastChild = node ;
			
		}
		node->parent = parent_node ;
	}
	
	
	//fprintf(stderr, "saiu2\n");
}

void AST_addChildren (AST* parent_node, AST* last_child)
{

	if(last_child != NULL)
	{
		AST* node = (AST*) malloc(sizeof(AST)) ;
		node = last_child ;
		//fprintf(stderr, "entrou3\n");
		parent_node->lastChild = node ;

		while (node->prevSibling != NULL)
		{
			node->parent = parent_node ;
			node = node->prevSibling ;
		}

		node->parent = parent_node ;
		parent_node->firstChild = node ;
		//fprintf(stderr, "saiu3\n");
	}
}

AST* AST_prependSibling(AST* right_node, AST* left_node)
{
	//fprintf(stderr, "entrou4\n");
	if(right_node != NULL && left_node != NULL)
	{
		while(left_node->nextSibling != NULL)
		{
			left_node = left_node->nextSibling ;
		}
		right_node->prevSibling = (AST*) malloc(sizeof(AST)) ;
		left_node->nextSibling = (AST*) malloc(sizeof(AST)) ;
		right_node->prevSibling = left_node ;
		left_node->nextSibling = right_node ;

		return left_node ;
	}

	else if(right_node != NULL && left_node == NULL)
		return right_node ;

	else if(right_node == NULL && left_node != NULL)
		return left_node ;
	else
		return NULL ;
	//fprintf(stderr, "saiu4\n");
	
}

AST* AST_newNumFromToken( int value, int line, int type)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	//fprintf(stderr, "entrou5\n");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = type ;
	node->intVal = value ;
	node->stringVal = NULL ;
	//fprintf(stderr, "saiu5\n");
	return node ;	
}

AST* AST_newStringFromToken( char* value, int line, int type)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	//fprintf(stderr, "entrou6\n");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = type ;
	node->intVal = 0 ;
	node->stringVal = value ;
	//fprintf(stderr, "saiu6\n");
	return node ;
}

void printAST (int type)
{
	if (type == 283)
		 fprintf(stderr, "AST_CHAR");
	else if (type == 284)
		fprintf(stderr, "AST_INT");
	else if (type == 285)
		fprintf(stderr, "AST_STRING");
	else if (type == 286)
		fprintf(stderr, "AST_BOOL");
	else if (type == 287)
		fprintf(stderr, "AST_TRUE");
	else if (type == 288)
		fprintf(stderr, "AST_FALSE");
	else if (type == 289)
		fprintf(stderr, "AST_NOT");
	else if (type == 290)
		fprintf(stderr, "AST_WHILE");
	else if (type == 291)
		fprintf(stderr, "AST_IF");
	else if (type == 292)
		fprintf(stderr, "AST_ELSE");
	else if (type == 293)
		fprintf(stderr, "AST_END");
	else if (type == 294)
		fprintf(stderr, "AST_NEW");
	else if (type == 295)
		fprintf(stderr, "AST_RET");
	else if (type == 296)
		fprintf(stderr, "AST_FUN");
	else if (type == 297)
		fprintf(stderr, "AST_GREATER");
	else if (type == 298)
		fprintf(stderr, "AST_LESS");
	else if (type == 299)
		fprintf(stderr, "AST_GREATER_EQUAL");
	else if (type == 300)
		fprintf(stderr, "AST_LESS_EQUAL");
	else if (type == 301)
		fprintf(stderr, "AST_EQUAL");
	else if (type == 302)
		fprintf(stderr, "AST_NOT_EQUAL");
	else if (type == 303)
		fprintf(stderr, "AST_PLUS");
	else if (type == 304)
		fprintf(stderr, "AST_MINUS");
	else if (type == 305)
		fprintf(stderr, "AST_TIMES");
	else if (type == 306)
		fprintf(stderr, "AST_DIVIDED");
	else if (type == 307)
		fprintf(stderr, "AST_AND");
	else if (type == 308)
		fprintf(stderr, "AST_OR");
	else if (type == 309)
		fprintf(stderr, "AST_ID");
	else if (type == 310)
		fprintf(stderr, "AST_PROGRAM");
	else if (type == 311)
		fprintf(stderr, "AST_GLOBAL");
	else if (type == 312)
		fprintf(stderr, "AST_BLOCK");
	else if (type == 313)
		fprintf(stderr, "AST_BLOCK_ELSE");
	else if (type == 314)
		fprintf(stderr, "AST_ELSEIF");
	else if (type == 315)
		fprintf(stderr, "AST_PARAM");
	else if (type == 316)
		fprintf(stderr, "AST_ATRIB");
	else if (type == 317)
		fprintf(stderr, "AST_NEG");
	else if (type == 318)
		fprintf(stderr, "AST_CALL");
	else if (type == 319)
		fprintf(stderr, "AST_DECLVAR");
	else if (type == 320)
		fprintf(stderr, "AST_NUMINT");
	else
		fprintf(stderr, "NO AST");
}
