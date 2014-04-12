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

AST AST_new (char* node_name, int line);
AST_addChildren (AST parent_node, AST first_child); 
AST_addChild (AST parent_node, AST node);
AST AST_prependSibling (AST right_node, AST left_node); 

#endif
