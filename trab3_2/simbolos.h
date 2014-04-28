#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "ast.h"
#include "tabela_simbolos.h"
#include <stdbool.h>

static bool fail(const char* msg, const char* name, AST* node); 
static bool Symbols_visitCall(SymbolTable* st, AST* call);
static bool Symbols_visitAssignInt(AST* assign, char* name, Symbol* existing);
static bool Symbols_visitAssignBool(AST* assign, char* name, Symbol* existing);
static bool Symbols_visitAssignChar(AST* assign, char* name, Symbol* existing);
static bool Symbols_visitAssign(SymbolTable* st, AST* assign);
static bool Symbols_visitDeclVar(SymbolTable* st, AST* declvar);
static bool Symbols_visitFunction(SymbolTable* st, AST* function);
bool Symbols_annotate(AST* program);

#endif
