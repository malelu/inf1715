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


SymbolTable* SymbolTable_new()
{
	SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable)) ;
	table->firstNode = NULL ;
	table->lastNode = NULL ;

	return table ;
}

NodeTable* NodeTable_new()
{
	NodeTable* table = (NodeTable*) malloc(sizeof(NodeTable)) ;
}

void SymbolTable_delete(SymbolTable* st)
{
}

void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line)
{

	Symbol sym = Symbol_new(name, type, line) ;
	st->lastSymbol
	st->lastSymbol = sym ;
}

Symbol* SymbolTable_get(SymbolTable* st, const char* name)
{
}
