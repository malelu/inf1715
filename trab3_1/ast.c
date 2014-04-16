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
		right_node->prevSibling = (AST*) malloc(sizeof(AST)) ;
		left_node->nextSibling = (AST*) malloc(sizeof(AST)) ;
		right_node->prevSibling = left_node ;
		left_node->nextSibling = right_node ;

		return right_node ;
	}

	else if(right_node != NULL && left_node == NULL)
		return right_node ;

	else if(right_node == NULL && left_node != NULL)
		return left_node ;
	else
		return NULL ;
	//fprintf(stderr, "saiu4\n");
	
}

AST* AST_newNumFromToken( int value)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	//fprintf(stderr, "entrou5\n");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = 0 ;
	node->type = 0 ;
	node->intVal = value ;
	node->stringVal = NULL ;
	//fprintf(stderr, "saiu5\n");
	return node ;	
}

AST* AST_newStringFromToken( char* value, int line)
{
	AST* node = (AST*) malloc(sizeof(AST)) ;
	//fprintf(stderr, "entrou6\n");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = 0 ;
	node->intVal = 0 ;
	node->stringVal = value ;
	//fprintf(stderr, "saiu6\n");
	return node ;
}

/*void AST_prettyPrinter (AST* node)
{
	print("%d", node->intVal) ;
	while (node->lastChild != NULL)
	{
		if(node->type != NULL)
			print("oi");
	}
}*/
