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

AST AST_new(node_name, int line);
AST_addChildren($$.node, $2.node); 
AST_addChild(parent_node, node);
AST AST_prependSibling(AST right_node, AST left_node); 

#endif
