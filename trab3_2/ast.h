#ifndef AST_H
#define AST_H

typedef struct AST_ AST;

struct AST_ {
   int type;
   int line;
   int intVal;
   char* stringVal;

   AST* firstChild;
   AST* lastChild;
   AST* parent;
   AST* nextSibling;
   AST* prevSibling;
};

enum ast { AST_CHAR = 283,
	     AST_INT,
	     AST_STRING,
	     AST_BOOL,
	     AST_TRUE,
	     AST_FALSE,
	     AST_NOT,  
	     AST_WHILE, 
	     AST_IF, 
	     AST_ELSE,
	     AST_END, 
	     AST_NEW, 
	     AST_RET, 
	     AST_FUN,
	     AST_GREATER,
	     AST_LESS, 
	     AST_GREATER_EQUAL,
	     AST_LESS_EQUAL, 
	     AST_EQUAL,
	     AST_NOT_EQUAL,
	     AST_PLUS,
	     AST_MINUS,
	     AST_TIMES,
	     AST_DIVIDED, 
	     AST_AND, 
	     AST_OR, 
	     AST_ID, 
	     AST_PROGRAM,
	     AST_GLOBAL,
	     AST_BLOCK,
	     AST_BLOCK_ELSE,
	     AST_ELSEIF,
	     AST_PARAM,
	     AST_ATRIB,
	     AST_NEG,
	     AST_CALL,
	     AST_DECLVAR,
	     AST_NUMINT
};

AST* AST_new (int node_type, int line);
void AST_addChildren (AST* parent_node, AST* first_child); 
void AST_addChild (AST* parent_node, AST* node);
AST* AST_prependSibling (AST* right_node, AST* left_node); 
AST* AST_newNumFromToken( int value, int line, int type) ;
AST* AST_newStringFromToken( char* value, int line, int type) ;
void AST_printAST (int type) ;

#endif
