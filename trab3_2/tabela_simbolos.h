#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdbool.h>

typedef enum {
   SYM_INT,
   SYM_CHAR,
   SYM_BOOL,
   SYM_FUN
} SymbolType;

typedef struct Symbol_ Symbol;

struct Symbol_ {
   char* name;
   SymbolType type;
   int line;
};

typedef struct NodeTable_ NodeTable;

struct NodeTable_ {
   	node* nextNode;
   	node* prevNode;
   	Symbol symbol ;
};

typedef struct SymbolTable_ SymbolTable;

struct SymbolTable_ {
	NodeTable* firstNode;
   	NodeTable* lastNode;
};

SymbolTable* SymbolTable_new();
void SymbolTable_delete(SymbolTable* st);
void SymbolTable_add(SymbolTable* st, const char* name, SymbolType type, int line);
Symbol* SymbolTable_get(SymbolTable* st, const char* name);

#endif
