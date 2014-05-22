#ifndef IR_H
#define IR_H

#include "ast.h"

typedef struct IR_ IR;

struct IR_ {
	int temps;
	int labels ;
};

/*typedef struct Params_ Params;

struct Params_ {
	char* param;
	Params* nextParam ;
};*/

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
   	NodeTable* firstCte ;
   	NodeTable* lastCte ;
	NodeFunc* nextFunc ;
	char* funcName ;
	char** params ;
	int numParams ; 
};

typedef struct IrTable_ IrTable;

struct IrTable_ {
	NodeFunc* firstNode;
	NodeFunc* lastNode ;
	IR* ir ;
};

IR* IR_gen(AST* program);

#endif
