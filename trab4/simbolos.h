#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "ast.h"
#include "tabela_simbolos.h"
#include <stdbool.h>

bool Symbols_annotate(AST* program);
void Symbols_printSYM(int type) ;

#endif
