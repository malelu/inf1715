#include "ast.h"

AST AST_new (char* node_type, int line)
{
	AST* node ;
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = line ;
	node->type = node_type ;
	node->intVal = NULL ;
	node->stringVal = NULL ;

	return node ;
}

void AST_addChild(parent_node, node)
{
	if(parent_node->firstChild == NULL)
	{
		parent_node->firstChild = node ;
		parent_node->lastChild = node ;
		
	}
	else
	{
		parent_node->lastChild->nextSibling = node ;
		node->previousSibling = parent_node->lastChild ;
		parent_node->lastChild = node ;
	}
	
	node->parent = parent_node ;
}

AST AST_addChildren (AST parent_node, AST last_child)
{
	last_child = node ;
	parent_node->lastChild = node ;

	while (node->prevSibling != NULL)
	{
		node->parent = parent_node ;
	}

	node->parent = parent_node ;
	parent_node->firstChild = node ;

	return parent_node ;

}

AST AST_prependSibling(AST right_node, AST left_node)
{
	right_node->previousSibling = left_node ;
	left_node->nextSibling = right_node ;

	return right_node ;
}

AST_newFromToken( int value) 
{
	AST* node ;
	node->firstChild = NULL ;
	node->lastChild = NULL ;
	node->parent = NULL ;
	node->nextSibling = NULL ;
	node->prevSibling = NULL ;
	node->line = NULL ;
	node->type = NULL ;
	node->intVal = value ;
	node->stringVal = NULL ;

	return node ;	
}

AST_prettyPrinter (AST node)
{
	print("%d", node->intVal) ;
	while (node->lastChild != NULL)
	{
		if(node->type != NULL)
			//print(type
	}
}
