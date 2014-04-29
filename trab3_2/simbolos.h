#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "ast.h"
#include "tabela_simbolos.h"
#include <stdbool.h>

static bool fail(const char* msg, const char* name, AST* node); 
int Symbols_visitExpression(SymbolTable* st, AST* exp);
static bool Symbols_visitIf(SymbolTable* st, AST* _if);
static bool Symbols_visitElseIf(SymbolTable* st, AST* else_if);
static bool Symbols_visitWhile(SymbolTable* st, AST* _while);
static bool Symbols_visitReturn(SymbolTable* st, AST* _return);
static bool Symbols_visitNew(SymbolTable* st, AST* _new) ;
static bool Symbols_visitParameter(SymbolTable* st, AST* parameter);
static bool Symbols_visitGlobal(SymbolTable* st, AST* global);
static bool Symbols_visitCall(SymbolTable* st, AST* call);
static bool Symbols_visitAssign(SymbolTable* st, AST* assign);
static bool Symbols_visitDeclVar(SymbolTable* st, AST* declvar);
static bool Symbols_visitFunction(SymbolTable* st, AST* function);
bool Symbols_annotate(AST* program);

#endif
