#ifndef IR_H
#define IR_H

#include "ast.h"

typedef struct IR_ IR;

struct IR_ {
	int temps;
	int labels ;
};

typedef struct NodeTable_ NodeTable;

struct NodeTable_ {
   	NodeTable* nextNode;
   	NodeTable* prevNode;
   	char* label ;
	char* operate ;
	char* op1 ;
	char* op2 ;
	char* op3 ;
};

typedef struct NodeFunc_ NodeFunc;

struct NodeFunc_ {
   	NodeTable* firstNode ;
	NodeFunc* nextFunc ;
	char* funcName ;
};

typedef struct IrTable_ IrTable;

struct IrTable_ {
	NodeFunc* firstFunc;
	IR* ir ;
   	//NodeTable* lastNode;
};

IR* IR_gen(AST* program);

#endif
