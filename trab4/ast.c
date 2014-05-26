#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* AST_new (int node_type, int line)
{
	
	AST* node = (AST*) malloc(sizeof(AST)) ;
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = node_type ;
	node->intVal = 0 ;
	node->stringVal = NULL ;
	node->symbol_type = -1 ;
	node->size = 0 ;

	return node ;
}

void AST_addChild(AST* parent_node, AST* node)
{
	if(node != NULL)
	{
		if(parent_node->firstChild == NULL)
		{
			parent_node->firstChild = (AST*) malloc(sizeof(AST)) ;
			parent_node->lastChild = (AST*) malloc(sizeof(AST)) ;	
			parent_node->firstChild = node ;
			while(node->nextSibling != NULL)
			{
				node = node->nextSibling ;
			}
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
}

void AST_addChildren (AST* parent_node, AST* last_child)
{

	if(last_child != NULL)
	{
		AST* node = (AST*) malloc(sizeof(AST)) ;
		node = last_child ;
		parent_node->lastChild = node ;

		while (node->prevSibling != NULL)
		{
			node->parent = parent_node ;
			node = node->prevSibling ;
		}

		node->parent = parent_node ;
		parent_node->firstChild = node ;
	}
}

AST* AST_prependSibling(AST* right_node, AST* left_node)
{
	if(right_node != NULL && left_node != NULL)
	{
		while(left_node->nextSibling != NULL)
		{
			left_node = left_node->nextSibling ;
		}
		while(right_node->prevSibling != NULL)
		{
			right_node = right_node->prevSibling ;
		}
		right_node->prevSibling = (AST*) malloc(sizeof(AST)) ;
		left_node->nextSibling = (AST*) malloc(sizeof(AST)) ;
		right_node->prevSibling = left_node ;
		left_node->nextSibling = right_node ;

		while(left_node->prevSibling != NULL)
		{
			left_node = left_node->prevSibling ;
		}

		return left_node ;
	}

	else if(right_node != NULL && left_node == NULL)
		return right_node ;

	else if(right_node == NULL && left_node != NULL)
	{
		return left_node ;
	}
	else
		return NULL ;
	
}

AST* AST_newNumFromToken( int value, int line, int type)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = type ;
	node->intVal = value ;
	node->stringVal = NULL ;
	return node ;	
}

AST* AST_newStringFromToken( char* value, int line, int type)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = type ;
	node->intVal = 0 ;
	node->stringVal = value ;
	return node ;
}

void AST_printAST (int type)
{
	if (type == 283)
		 fprintf(stdout, "AST_CHAR");
	else if (type == 284)
		fprintf(stdout, "AST_INT");
	else if (type == 285)
		fprintf(stdout, "AST_STRING");
	else if (type == 286)
		fprintf(stdout, "AST_BOOL");
	else if (type == 287)
		fprintf(stdout, "AST_TRUE");
	else if (type == 288)
		fprintf(stdout, "AST_FALSE");
	else if (type == 289)
		fprintf(stdout, "AST_NOT");
	else if (type == 290)
		fprintf(stdout, "AST_WHILE");
	else if (type == 291)
		fprintf(stdout, "AST_IF");
	else if (type == 292)
		fprintf(stdout, "AST_ELSE");
	else if (type == 293)
		fprintf(stdout, "AST_END");
	else if (type == 294)
		fprintf(stdout, "AST_NEW");
	else if (type == 295)
		fprintf(stdout, "AST_RET");
	else if (type == 296)
		fprintf(stdout, "AST_FUN");
	else if (type == 297)
		fprintf(stdout, "AST_GREATER");
	else if (type == 298)
		fprintf(stdout, "AST_LESS");
	else if (type == 299)
		fprintf(stdout, "AST_GREATER_EQUAL");
	else if (type == 300)
		fprintf(stdout, "AST_LESS_EQUAL");
	else if (type == 301)
		fprintf(stdout, "AST_EQUAL");
	else if (type == 302)
		fprintf(stdout, "AST_NOT_EQUAL");
	else if (type == 303)
		fprintf(stdout, "AST_PLUS");
	else if (type == 304)
		fprintf(stdout, "AST_MINUS");
	else if (type == 305)
		fprintf(stdout, "AST_TIMES");
	else if (type == 306)
		fprintf(stdout, "AST_DIVIDED");
	else if (type == 307)
		fprintf(stdout, "AST_AND");
	else if (type == 308)
		fprintf(stdout, "AST_OR");
	else if (type == 309)
		fprintf(stdout, "AST_ID");
	else if (type == 310)
		fprintf(stdout, "AST_PROGRAM");
	else if (type == 311)
		fprintf(stdout, "AST_GLOBAL");
	else if (type == 312)
		fprintf(stdout, "AST_BLOCK");
	else if (type == 313)
		fprintf(stdout, "AST_BLOCK_ELSE");
	else if (type == 314)
		fprintf(stdout, "AST_ELSEIF");
	else if (type == 315)
		fprintf(stdout, "AST_PARAM");
	else if (type == 316)
		fprintf(stdout, "AST_ATRIB");
	else if (type == 317)
		fprintf(stdout, "AST_NEG");
	else if (type == 318)
		fprintf(stdout, "AST_CALL");
	else if (type == 319)
		fprintf(stdout, "AST_DECLVAR");
	else if (type == 320)
		fprintf(stdout, "AST_NUMINT");
	else if (type == 321)
		fprintf(stdout, "AST_LITERAL_STRING");
	else if (type == 322)
		fprintf(stdout, "AST_LOOP");
	else
		fprintf(stdout, "NO AST");
}
