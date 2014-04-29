#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {
   SYM_INT,
   SYM_CHAR,
   SYM_BOOL,
   SYM_FUN
} SymbolType;

typedef struct Symbol_ Symbol;

struct Symbol_ {
   const char* name;
   SymbolType type;
   int line;
   int size;

   int* fun_param ;
   int fun_ret ;
};

typedef struct NodeTable_ NodeTable;

struct NodeTable_ {
   	NodeTable* nextNode;
   	NodeTable* prevNode;
   	Symbol* symbol ;
	int level ;
};

typedef struct SymbolTable_ SymbolTable;

struct SymbolTable_ {
	NodeTable* firstNode;
   	NodeTable* lastNode;
};

Symbol* Symbol_new(const char* name, SymbolType type, int line, int size, int num_param, int* fun_param, int fun_ret) ;
NodeTable* NodeTable_new(Symbol* sym) ;
SymbolTable* SymbolTable_new();
void SymbolTable_delete(SymbolTable* st);
void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line, int size, int num_param, int* fun_param, int fun_ret);
Symbol* SymbolTable_get(SymbolTable* st, const char* name);

#endif
