#ifndef IR_H
#define IR_H

#include "ast.h"

typedef struct IR_ IR;

struct IR_ {
   int temps;
};

typedef struct NodeTable_ NodeTable;

struct NodeTable_ {
   	NodeTable* nextNode;
   	NodeTable* prevNode;
   	Symbol* symbol ;
};

typedef struct IrTable_ IrTable;

struct IrTable_ {
	NodeTable* firstNode;
   	NodeTable* lastNode;
};

IR* IR_gen(AST* program);

#endif
