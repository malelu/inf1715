#include "tabela_simbolos.h"


Symbol* Symbol_new(char* name, SymbolType type, int line)
{
   	Symbol* sym = (Symbol*) malloc(sizeof(Symbol)) ;
	sym->name = name ;
	sym->type = (SymbolType*) malloc(sizeof(SymbolType)) ;
	sym->type = type ;
	sym->line = line ;

	return sym ;
}

NodeTable* NodeTable_new(Symbol* sym)
{
	NodeTable* node = (NodeTable*) malloc(sizeof(NodeTable)) ;
	node->nextNode = NULL;
   	node->prevNode = NULL;
   	node->symbol = (Symbol*) malloc(sizeof(Symbol)) ;
	node->Symbol = sym ;

	return node ;
}


SymbolTable* SymbolTable_new()
{
	SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable)) ;
	table->firstNode = NULL ;
	table->lastNode = NULL ;

	return table ;
}


void SymbolTable_delete(SymbolTable* st)
{

	Node* node = st->firstNode ;
	while(node != NULL)
	{
		Node next = node->nextNode ;
		free(node) ;
		node = next ;
	}

	free(st) ;
}

void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line)
{

	Symbol* sym = Symbol_new(name, type, line) ;
	NodeTable* new_node = NodeTable_new(&sym) ;
	NodeTable* old_last_node = NULL;
	
	if(st->firstNode == NULL)
	{
		st->firstNode = (NodeTable*) malloc(sizeof(NodeTable)) ;
		st->lastNode = (NodeTable*) malloc(sizeof(NodeTable)) ;
		st->firstNode = new_node ;
		st->lastNode = new_node ; 
	}
	else
	{
		old_last_node = (NodeTable*) malloc(sizeof(NodeTable)) ;
		new_node->prevNode = (NodeTable*) malloc(sizeof(NodeTable)) ;

		old_last_node = st->lastNode ;
		old_last_node->nextNode = new_node ;
		new_node->prevNode = old_last_node ;
		st->lastNode = new_node ;
	}
}

Symbol* SymbolTable_get(SymbolTable* st, const char* name)
{

	NodeTable* node = (NodeTable*) malloc(sizeof(NodeTable)) ;
	node = st->firstNode ;

	while(strcmp(node->symbol->name, name) != 0)
	{
		if(node->nextNode == NULL)
		{
			fprintf(stderr, "no symbol match this name") ;
			return NULL ;
		}			
		node = node->nextNode ;
	}

	return node->Symbol ;
	
}
