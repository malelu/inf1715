#include "ast.h"

AST AST_new(node_name, int line)
{
	AST node ;
	node.line = line ;
	node.type
}

AST_addChild(parent_node, node)
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

AST AST_prependSibling(AST right_node, AST left_node)
{
	right_node->previousSibling = left_node ;
	left_node->nextSibling = right_node ;
}
