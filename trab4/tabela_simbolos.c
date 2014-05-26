#include "tabela_simbolos.h"


Symbol* Symbol_new(const char* name, SymbolType type, int line, int size, int scope, int num_param, int fun_param[][2], int* fun_ret)
{

	//fprintf(stderr, "entrou symbol new\n") ;
   	Symbol* sym = (Symbol*) malloc(sizeof(Symbol)) ;
	sym->name = name ;
	sym->type = type ;
	sym->line = line ;
	sym->fun_ret[0] = fun_ret[0] ;
	sym->fun_ret[1] = fun_ret[1] ;
	sym->size = size ;
	sym->scope = scope;

	if (num_param >0 )
	{
		int cont = 0 ;
		while (cont < num_param)
		{
			sym->fun_param[cont][0] = fun_param[cont][0] ;
			sym->fun_param[cont][1] = fun_param[cont][1] ;
			cont++;
		}

		sym->fun_param[cont][0] = -1 ; //indica que acabou
		sym->fun_param[cont][1] = -1 ;
	}

	
	//fprintf(stderr, "saiu symbol new\n") ;
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

void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line, int size, int scope,
			 int num_param, int fun_param[][2], int* fun_ret)
{
	fprintf(stderr, "entrou add symbol table\n") ;
	fprintf(stderr, "name: %s, type: %d\n", name, type) ;
	Symbol* sym = Symbol_new(name, type, line, size, scope, num_param, fun_param, fun_ret) ;
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

Symbol* SymbolTable_get(SymbolTable* st, const char* name, int scope)
{
	//fprintf(stderr, "entrou get\n") ;
	NodeTable* node = (NodeTable*) malloc(sizeof(NodeTable)) ;
	node = st->lastNode ;

	//fprintf(stderr, "etab\n") ;
	//fprintf(stderr, "%d\n", node) ;
	printf("GET name: %s\n", name) ;
	if (node != NULL)
	{
		while((strcmp(node->symbol->name, name) != 0))// || ((strcmp(node->symbol->name, name) == 0) && (node->symbol->scope != scope)))
		{
			//printf("get node->symbol->name: %s\n", node->symbol->name) ;
			//printf("get node->symbol->scope: %d\n", node->symbol->scope) ;
			//printf("get scope: %d\n", scope) ;
			if(node->prevNode == NULL)
			{
				//fprintf(stderr, "no symbol match this name\n") ;
				return NULL ;
			}	

			//if((strcmp(node->symbol->name, name) == 0) && (node->symbol->scope == -1))	//é global
			//{
				//fprintf(stderr, "É GLOBAL\n") ;
			//	return node->symbol ;
			//}	
			node = node->prevNode ;
		}
		
		/*fprintf(stderr, "NOME DO NÓ %s\n", name) ;
		fprintf(stderr, "NOME DO NÓ ENCONTRADO %s\n", node->symbol->name) ;
		fprintf(stderr, "SCOPE DA TABELA %d\n", node->symbol->scope) ;
		fprintf(stderr, "SCOPE DO NÓ %d\n", scope) ;
		fprintf(stderr, "LINHA DO NÓ ENCONTRADO %d\n", node->symbol->line) ;
		fprintf(stderr, "saiu get\n") ;*/
		return node->symbol ;
	}
	fprintf(stderr, "SAIU get\n") ;
	return NULL ;
	
}


void SymbolTable_print(SymbolTable* st)
{
	NodeTable* node = (NodeTable*) malloc(sizeof(NodeTable)) ;
	node = st->firstNode ;

	if(node != NULL)
	{
		//printf(stderr, "entrou imprime tabela\n") ;
		while(node->prevNode != NULL)
		{
			//fprintf(stderr, "entrou 2imprime tabela\n") ;
			fprintf(stderr, "name %s\t", node->symbol->name) ;
			fprintf(stderr, "type %s\t", node->symbol->type) ;
			fprintf(stderr, "line %s\t", node->symbol->line) ;
			fprintf(stderr, "size %s\t", node->symbol->size) ;
			fprintf(stderr, "scope %s\t", node->symbol->scope) ;
			fprintf(stderr, "\n");
			node = node->prevNode ;
		}
	}
}
