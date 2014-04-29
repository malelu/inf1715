#include "tabela_simbolos.h"


Symbol* Symbol_new(const char* name, SymbolType type, int line, int size, int num_param, int* fun_param, int fun_ret)
{
   	Symbol* sym = (Symbol*) malloc(sizeof(Symbol)) ;
	sym->name = name ;
	sym->type = type ;
	sym->line = line ;
	sym->fun_ret = fun_ret ;
	sym->size = size ;

	if (num_param >0 )
	{
		int cont = 0 ;
		sym->fun_param = (int*)malloc(num_param*sizeof(int)) ;
		while (cont < num_param)
		{
			sym->fun_param[cont] = fun_param[cont] ;
		}
	}

	

	return sym ;
}

NodeTable* NodeTable_new(Symbol* sym)
{
	NodeTable* node = (NodeTable*) malloc(sizeof(NodeTable)) ;
	node->nextNode = NULL;
   	node->prevNode = NULL;
   	node->symbol = (Symbol*) malloc(sizeof(Symbol)) ;
	node->symbol = sym ;

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

	NodeTable* node = st->firstNode ;
	NodeTable* next ;
	while(node != NULL)
	{
		next = node->nextNode ;
		free(node) ;
		node = next ;
	}

	free(st) ;
}

void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line, int size, int num_param, int* fun_param, int fun_ret)
{

	Symbol* sym = Symbol_new(name, type, line, size, num_param, fun_param, fun_ret) ;
	NodeTable* new_node = NodeTable_new(sym) ;
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

fprintf(stderr, "etab\n") ;
fprintf(stderr, "%d\n", node) ;
	if (node != NULL)
	{
		while(strcmp(node->symbol->name, name) != 0)
		{
			if(node->nextNode == NULL)
			{
				fprintf(stderr, "no symbol match this name") ;
				return NULL ;
			}			
			node = node->nextNode ;
		}

		return node->symbol ;
	}

	return NULL ;
	
}
