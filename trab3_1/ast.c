#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

AST* AST_new (int node_type, int line)
{
	
	AST* node = (AST*) malloc(sizeof(AST)) ;
	printf("oi");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = node_type ;
	node->intVal = 0 ;
	node->stringVal = NULL ;

	return node ;
}

void AST_addChild(AST* parent_node, AST* node)
{
	printf("oi");
	if(parent_node->firstChild == NULL)
	{
		parent_node->firstChild = node ;
		parent_node->lastChild = node ;
		
	}
	else
	{
		parent_node->lastChild->nextSibling = node ;
		node->prevSibling = parent_node->lastChild ;
		parent_node->lastChild = node ;
	}
	
	node->parent = parent_node ;
}

void AST_addChildren (AST* parent_node, AST* last_child)
{
	printf("oi");
	AST* node = last_child ;
	printf("oi");
	parent_node->lastChild = node ;

	while (node->prevSibling != NULL)
	{
		node->parent = parent_node ;
	}

	node->parent = parent_node ;
	parent_node->firstChild = node ;

}

AST* AST_prependSibling(AST* right_node, AST* left_node)
{
	printf("oi");
	right_node->prevSibling = left_node ;
	left_node->nextSibling = right_node ;

	return right_node ;
}

AST* AST_newNumFromToken( int value)
{
	printf("oi");
	AST* node ;
	printf("oi");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = 0 ;
	node->type = 0 ;
	node->intVal = value ;
	node->stringVal = NULL ;

	return node ;	
}

AST* AST_newStringFromToken( char* value)
{
	printf("oi");
	AST* node ;
	printf("oi");
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = 0 ;
	node->type = 0 ;
	node->intVal = 0 ;
	node->stringVal = value ;

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
