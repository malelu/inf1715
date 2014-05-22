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

typedef struct NodeCte_ NodeCte;

struct NodeCte_ {
   	NodeCte* nextNode;
   	NodeCte* prevNode;
   	char* label ;
	char* operand ;
	char* op1 ;
	char* op2 ;
	char* op3 ;
};

typedef struct NodeFunc_ NodeFunc;

struct NodeFunc_ {
   	NodeCte* firstCte ;
   	NodeCte* lastCte ;
	NodeFunc* nextFunc ;
	char* funcName ;
	char** params ;
	int numParams ; 
};

typedef struct OpTable_ OpTable;

struct OpTable_ {
	NodeFunc* firstNode;
	NodeFunc* lastNode ;
	IR* ir ;
};

OpTable* IR_gen(AST* program);

#endif
