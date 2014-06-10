#ifndef IR_H
#define IR_H

#include <stdio.h>

/*
Opcodes for IR instructions.
*/
typedef enum Opcode_ {
OP_LABEL,
OP_GOTO,
OP_IF,
OP_IF_FALSE,
OP_SET,
OP_SET_BYTE,
OP_SET_IDX,
OP_SET_IDX_BYTE,
OP_IDX_SET,
OP_IDX_SET_BYTE,
OP_PARAM,
OP_CALL,
OP_RET,
OP_RET_VAL,
OP_NE,
OP_EQ,
OP_LT,
OP_GT,
OP_LE,
OP_GE,
OP_ADD,
OP_SUB,
OP_DIV,
OP_MUL,
OP_NEG,
OP_NEW,
OP_NEW_BYTE,
} Opcode;

/*
Types of things that may go into the x, y and z addresses
in three-address code instructions.
*/
typedef enum AdType_ {
AD_UNSET = 0, // Used only in instructions with less than three addresses.
AD_GLOBAL,
AD_LOCAL,
AD_TEMP,
AD_LABEL,
AD_STRING,
AD_NUMBER,
AD_FUNCTION
} AdType;

/*
An "address" x, y and z used in three-address instructions.
*/
typedef struct Addr_ {
AdType type;
/*
String representation of this entry
(literal string, label name, variable name, function name)
*/
char* str;
/*
For AD_GLOBAL, AD_LOCAL and AD_TEMP entries,
num contains the index of the respective global, local or temp.
For AD_NUMBER entries, num contains the numeric value.
For other entries, num is zero.
*/
int num;	
} Addr;

typedef struct List_ List;
struct List_ {
List* next;
};




/*
ListLife
*/
typedef struct ListLife_ ListLife;
struct ListLife_ {
int alive;
int nextPosAlive ;
int posTable ;
ListLife* next ;
ListLife* previous ;
};


/*
ListName
*/
typedef struct ListName_ ListName;
struct ListName_ {
char* name;
ListName* nextName ;
ListLife* first ;
ListLife* last ;
int status ;
};

/*
Registrer table
*/
typedef struct RegList_ RegList;
struct RegList_ {
char* reg1 ;
char* reg2 ;
char* reg3 ;
ListName* firstName;
ListName* lastName;

};

/*
An instruction in the three-address code format of our IR.
Instructions are stored as a linked list.
*/
typedef struct Instr_ Instr;
typedef struct InstrMod_ InstrMod;
struct InstrMod_ {
InstrMod* next;
InstrMod* prev ;
Instr* instr ;
};


/*
Life table
*/
typedef struct LifeTable_ LifeTable;
struct LifeTable_ {
ListName* firstName;
ListName* lastName;
LifeTable* next ;
RegList* regs ;
int qtdNames ;
int qtdLines ;
InstrMod* firstInstructions;
InstrMod* lastInstructions;
};

/*
Basic Block
*/
typedef struct BasicBlock_ BasicBlock;
struct BasicBlock_ {
LifeTable* life ;
RegList* registrer ;
int basicNum ;
};


/*
An instruction in the three-address code format of our IR.
Instructions are stored as a linked list.
*/
//typedef struct Instr_ Instr;
struct Instr_ {
Instr* next;
Opcode op;
Addr x;
Addr y;
Addr z;
BasicBlock* bBlock ;
};

/*
A literal string.
Strings are stored as a linked list.
*/
typedef struct String_ String;
struct String_ {
String* next;
const char* name;
const char* value;
};

/*
A variable. This is used to represent globals, locals and temps.
Variables are stored as a linked list.
*/
typedef struct Variable_ Variable;
struct Variable_ {
Variable* next;
const char* name;
};

/*
A function.
Functions are stored as a linked list.
*/
typedef struct Function_ Function;
struct Function_ {
Function* next;
/*
Name of the function.
*/
const char* name;
/*
Number of input arguments of this function.
The first `nArgs` entries in the `locals` list below are
the input arguments.
*/
int nArgs;
/*
All locals used by a function.
This list is constructed as the file is parsed,
with no duplicates. Therefore, a variable can be referenced
uniquely by its position in this list, which is stored in
the .num field of its Addr in every Instr where it is used.
*/
Variable* locals;
/*
All temps used by a function.
Temps are stored separately from locals in case it is
convenient to make the distinction. It is easy to change
the code in Addr_resolve to make all temps go into
the locals list instead.
*/
Variable* temps;
/*
The linked list of instructions.
*/
Instr* code;
};

/*
An IR program.
*/
typedef struct IR_ {
Variable* globals;
String* strings;
Function* functions;
} IR;

// -------------------- Functions, documented in ir.c --------------------

List* List_link(List* elem, List* list);

IR* IR_new();
void IR_setStrings(IR* ir, String* strings);
void IR_setGlobals(IR* ir, Variable* globals);
void IR_addFunction(IR* ir, Function* fun);
void IR_dump(IR* ir, FILE* fd);

String* String_new(char* name, char* value);
#define String_link(_l1, _l2) ((String*)List_link((List*)(_l1), (List*)(_l2)))

Variable* Variable_new(char* name);
#define Variable_link(_l1, _l2) ((Variable*)List_link((List*)(_l1), (List*)(_l2)))

Instr* Instr_new(Opcode op,  ...);
#define Instr_link(_l1, _l2) ((Instr*)List_link((List*)(_l1), (List*)(_l2)))

Addr Addr_litNum(int num);
Addr Addr_label(char* label);
Addr Addr_function(char* name);
Addr Addr_resolve(char* name, IR* ir, Function* fun);

Function* Function_new(char* name, Variable* args);

#endif
