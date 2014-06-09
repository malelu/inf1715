#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ir.h"

int basicBlock = 0 ;
int totalBlockLines ;

// -------------------- List --------------------

/*
Given an element and a list, make it a new list
with the given element as the head ("cons" a.k.a. (x:xs) operation).
*/
List* List_link(List* elem, List* list) 
{
	if (!elem) 
	{
		return list;
	}
	elem->next = list;
	return elem;
}

// -------------------- String --------------------

/*
Allocate a new string entry.
*/
String* String_new(char* name, char* value) 
{
	String* str = calloc(1, sizeof(String));
	str->name = name;
	str->value = value;
	return str;
}

// -------------------- Variable --------------------

/*
Allocate a new variable entry.
Lists of variables are used for globals, locals and temps.
*/
Variable* Variable_new(char* name) 
{
	Variable* var = calloc(1, sizeof(Variable));
	var->name = name;
	return var;
}

/*
Add variable var to the end of the list.
*/
Variable* Variable_append(Variable* list, Variable* var) 
{
	if (!list) 
	{
		return var;
	}
	Variable* last = list;
	while (last->next) 
	{
		last = last->next;
	}
	last->next = var;
	return list;
}

/*
Given a name, return a variable (plus its position in variable *pos).
This function actually works for String lists as well,
because they are structurally compatible.
*/
static Variable* Variable_find(Variable* list, const char* name, int* pos) 
{
	int i;
	Variable* v;
	for (v = list, i = 0; v; v = v->next, i++) 
	{
		if (strcmp(name, v->name) == 0) 
		{
			*pos = i;
			return v;
		}
	}
	*pos = i;
	return NULL;
}

// -------------------- Addr --------------------

/*
Create an Addr entry for literal numbers.
*/
Addr Addr_litNum(int num) 
{
	Addr addr;
	addr.type = AD_NUMBER;
	addr.num = num;
	char* str = malloc(21);
	snprintf(str, 20, "%d", num);
	addr.str = str;
	return addr;
}

/*
Create an Addr entry for labels.
*/
Addr Addr_label(char* label) 
{
	Addr addr;
	addr.type = AD_LABEL;
	addr.num = -1;
	addr.str = label;
	return addr;
}

/*
Create an Addr entry for function names.
*/
Addr Addr_function(char* name) 
{
	Addr addr;
	addr.type = AD_FUNCTION;
	addr.num = -1;
	addr.str = name;
	return addr;
}

/*
This function produces an Addr from a given name.

If the name matches an existing global, local or temp,
it returns an Addr containing its name and index.

If the name is not found, it creates and store a
new local or temp entry, and returns an Addr with
its name and index.
*/
Addr Addr_resolve(char* name, IR* ir, Function* fun) 
{
	Addr addr;
	addr.str = name;
	if (name[0] == '$') 
	{
		int i;
		Variable* v = Variable_find(fun->temps, name, &i);
		if (!v) 
		{
			v = Variable_new(name);
			fun->temps = Variable_append(fun->temps, v);
		}
		addr.type = AD_TEMP;
		addr.num = i;
		return addr;
	}
	int i;
	Variable* v = Variable_find(ir->globals, name, &i);
	if (v) 
	{
		addr.type = AD_GLOBAL;
		addr.num = i;
		return addr;
	}
	String* s = (String*) Variable_find((Variable*) ir->strings, name, &i);
	if (s) 
	{
		addr.type = AD_STRING;
		addr.num = i;
		return addr;
	}
	addr.type = AD_LOCAL;
	v = Variable_find(fun->locals, name, &i);
	if (v) 
	{
		addr.num = i;
		return addr;
	}
	v = Variable_new(name);
	fun->locals = Variable_append(fun->locals, v);
	addr.num = i;
	return addr;
}

/*
Use this function to compare two Addrs.
This way no string comparison is necessary.
*/
bool Addr_eq(Addr a1, Addr a2) 
{
	return (a1.type == a1.type && a1.num == a1.num);
}


//--------------------- InstrMod --------------

InstrMod* InstrMod_new(Instr* ins)
{
	InstrMod* new_mod = calloc(1, sizeof(InstrMod));
	new_mod->next = NULL;
	new_mod->prev = NULL;
	new_mod->instr = ins;
	return new_mod ;
}


//--------------------- List Life --------------

ListLife* ListLife_new(int posTable, int alive, int nextPosAlive)
{
	ListLife* new_listLife = calloc(1, sizeof(ListLife));
	new_listLife->alive = alive ; // 0 = dead ; 1 = alive
	new_listLife->nextPosAlive = nextPosAlive ;
	new_listLife->posTable = posTable ;
	new_listLife->next = NULL;
	new_listLife->previous = NULL;
	return new_listLife ;
}


//--------------------- list Name --------------

ListName* ListName_new(char* name)
{
	ListName* new_listName = calloc(1, sizeof(ListName));
	new_listName->name = name ;
	new_listName->nextName = NULL ;
	new_listName->first = NULL ;
	new_listName->last = NULL ;
	return new_listName ;
}

//--------------------- Reg List --------------

RegList* regList_new()
{
	RegList* regs = calloc(1, sizeof(RegList));
	regs->firstName = NULL ;
	regs->lastName = NULL ;
	regs->reg1 = NULL ;
	regs->reg2 = NULL ;
	regs->reg3 = NULL ;
	return regs ;
}

//--------------------- Life Table --------------

LifeTable* lifeTable_new()
{
	LifeTable* new_lifeTable = calloc(1, sizeof(LifeTable));
	new_lifeTable->firstName = NULL ;
	new_lifeTable->lastName = NULL ;
	new_lifeTable->next = NULL ;
	new_lifeTable->qtdNames = 0 ;
	new_lifeTable->qtdLines = 0 ;
	new_lifeTable->firstInstructions = NULL ;
	new_lifeTable->lastInstructions = NULL ;
	return new_lifeTable ;
}

//--------------------- Basic Block --------------

BasicBlock* basicBlock_new()
{
	BasicBlock* new_block = calloc(1, sizeof(BasicBlock));
	new_block->life = NULL ;
	new_block->registrer = NULL ;
	new_block->basicNum = 0 ;
	return new_block ;
}

//--------------- Inserting into list of names ---------

void InsertListName (char* name, LifeTable* tab)
{
	if(tab->firstName == NULL)
	{
		tab->firstName = ListName_new(name) ;
		tab->lastName = tab->firstName ;
	}	
	else
	{
		ListName* oldLast = tab->lastName ;
		tab->lastName = ListName_new(name) ;
		oldLast->nextName = tab->lastName ;		
	}
}

//-------- Inserting into list of names of registrer ------

void InsertRegsListName (char* name, RegList* regs)
{
	if(regs->firstName == NULL)
	{
		regs->firstName = ListName_new(name) ;
		regs->lastName = regs->firstName ;
	}	
	else
	{
		ListName* oldLast = regs->lastName ;
		regs->lastName = ListName_new(name) ;
		oldLast->nextName = regs->lastName ;		
	}
}

//-------------------- Not Repeated --------------------

bool notRepeated(char* name, LifeTable* lifeTab)
{
	ListName* lstName = lifeTab->firstName ;
	while(lstName)
	{
		if(strcmp(lstName->name, name) == 0)
			return false ; 
		lstName = lstName->nextName ;
	}
	return true ;
} 

// -------------------- Insert instructions -----------

void insertListLifeInstructions (LifeTable* lifeTab, InstrMod* mod)
{
				printf("mod->instr->x.str %s\n", mod->instr->x.str) ;
				//printf("mod->instr->y.str %s\n", mod->instr->y.str) ;
				//printf("mod->instr->z.str %s\n", mod->instr->z.str) ;
	if(lifeTab->firstInstructions == NULL)
	{
		lifeTab->firstInstructions = mod ;
		lifeTab->lastInstructions = mod ;
	}
	else
	{
		InstrMod* prevLastInst = lifeTab->lastInstructions ;
		lifeTab->lastInstructions = mod;
		prevLastInst->next = lifeTab->lastInstructions ;
		lifeTab->lastInstructions->prev = prevLastInst ;
		//printf("lifeTab->lastInstructions->prev->instr->x.str %s\n", lifeTab->lastInstructions->prev->instr->x.str) ;
	}
}

//-------------------- Inserting into life table and registrer -------

void InsertLifeTable (Instr* code, LifeTable* lifeTab, RegList* regs)
{
	char* name = malloc(20) ;
	if((code->op == OP_IDX_SET) || (code->op == OP_IDX_SET_BYTE))
	{
		snprintf(name, 20, "%s[%s]", code->x.str, code->y.str);
	}
	else
	{
		strcpy(name, code->x.str) ;	
	}
		
	if(notRepeated(name, lifeTab))
	{
		printf("name: %s\n", name) ;
		InsertListName (name, lifeTab) ;
		InsertRegsListName (name, regs) ;
		lifeTab->qtdNames = lifeTab->qtdNames + 1 ;
	}

	lifeTab->qtdLines = lifeTab->qtdLines + 1 ;
	//printf("bloco basico: %d\n", code->bBlock->basicNum) ;
	//printf("num linhas: %d\n", lifeTab->qtdLines) ;
}

//-------------------- valid variable -------

bool validVariable (Instr* ins)
{
	if((ins->op == OP_NE) || (ins->op == OP_LT) || (ins->op == OP_GT) || (ins->op == OP_LE) || (ins->op == OP_GE) ||
		(ins->op == OP_ADD) || (ins->op == OP_SUB) || (ins->op == OP_DIV) || (ins->op == OP_MUL) || (ins->op == OP_NEG) ||
		(ins->op == OP_NEW) || (ins->op == OP_NEW_BYTE) || (ins->op == OP_SET) || (ins->op == OP_SET_BYTE) ||
		(ins->op == OP_SET_IDX) || (ins->op == OP_SET_IDX_BYTE) || (ins->op == OP_IDX_SET) || (ins->op == OP_IDX_SET_BYTE))
		return true ;
	return false ;
}

//-------------------- Creating life table -------

void CreateLifeTable (IR* ir)
{
	Function* lastFn = ir->functions;
	LifeTable* lifeTab = NULL;
	LifeTable* prevTable = lifeTab ;
	RegList* regs = NULL ;
	printf("lifeTab inicial %d\n", lifeTab) ;
	LifeTable* aux ;

	while (lastFn) 
	{
		Instr* ins = lastFn->code ;

		prevTable = lifeTab ;
		lifeTab = lifeTable_new() ;		//cada nova funcao é o início de uma nova tabela
		regs = regList_new() ;
		lifeTab->regs = regs ;
		if(prevTable != NULL)
			prevTable->next = lifeTab ;
		printf("NEW BLOCK1 \n") ;
		printf("lifeTab %d\n", lifeTab) ;
		printf("lifeTab->next %d\n", lifeTab->next) ;
		int bBlock = ins->bBlock->basicNum ;
		while(ins)
		{			
			if(validVariable(ins))
			{
				if(bBlock == (ins->bBlock->basicNum))	//while por bloco básico
				{
					InsertLifeTable(ins, lifeTab, regs) ;		// insere na tabela de registradores a nova variável
					//printf("ins %d\n", ins) ;
				}
				else
				{
					bBlock = ins->bBlock->basicNum ;
					prevTable = lifeTab;
					lifeTab = lifeTable_new() ;		//cada novo bloco é o início de uma nova tabela
					regs = regList_new() ;
					lifeTab->regs = regs ;
					prevTable->next = lifeTab ;
					printf("prevTable %d\n", prevTable) ;
					printf("prevTable->next %d\n", prevTable->next) ;
					printf("NEW BLOCK2 \n") ;
					InsertLifeTable(ins, lifeTab, regs) ;
				}
			}
			else
			{
				lifeTab->qtdLines = lifeTab->qtdLines + 1 ;
			}
			ins->bBlock->life = lifeTab ;
			ins->bBlock->registrer = regs ;
			InstrMod* mod = InstrMod_new(ins) ;
			insertListLifeInstructions (lifeTab, mod) ;
			ins = ins->next ;
		}
		// printando mod------------------------
		InstrMod* mod2 = lifeTab->lastInstructions ;
		while(mod2)
		{
			printf("--mod2->instr->x.str %s\n", mod2->instr->x.str) ;
			mod2 = mod2->prev ;
		}
		//-------------------------------------------
		lastFn = lastFn->next;
	}

	aux = ir->functions->code->bBlock->life ;
	while(aux)
	{
		//printf("TABELA!\n") ; 
		aux = aux->next ;
	}
}

// -------------------- Insert ListLife -----------

void insertListLife (ListName* lstName, ListLife* lstLife)
{
	if(lstName->first == NULL)
	{
		lstName->first = lstLife ;
		lstName->last = lstName->first ;
	}
	else
	{
		ListLife* nextLst = lstName->first ;
		lstName->first = lstLife ;
		nextLst->previous = lstName->first ; 
		lstName->first->next = nextLst ;
	}
}

// -------------------- Fill Life Table Status -----
void FillLifeTableStatus (IR* ir)
{
	LifeTable* lifeTab = ir->functions->code->bBlock->life;
	ListName* lstName = lifeTab->firstName ;
	ListLife* lstLife ;
	int cont ;
	int nextPosAlive = -1 ;
	InstrMod* mod ;

	while (lifeTab) 		// cria estruturas listLife
	{
		lstName = lifeTab->firstName ;
		while(lstName)
		{	
			//printf("---LSTNAME->NAME: %s\n", lstName->name) ;
			mod =  lifeTab->lastInstructions ;
			lstLife = ListLife_new(lifeTab->qtdLines, 1, nextPosAlive) ;
			//printf("---LSTLIFE1: %d\n", lstLife) ;
			insertListLife (lstName, lstLife) ;  // na última linha está sempre vivo

		// printando mod------------------------
		while(mod)
		{
			printf("====mod//->instr->x.str %s\n", mod->instr->x.str) ;
			mod = mod->prev ;
		}
		mod =  lifeTab->lastInstructions ;
		//-------------------------------------------	
	
			for(cont=lifeTab->qtdLines-1;cont>=0;cont--)
			{//printf("---0 \n") ;
				//if(mod == NULL)
					//break ;
				printf("--mod//->instr->x.str %s\n", mod->instr->x.str) ;

				// checa se está do lado esquerdo da igualdade
				if((mod->instr->x.str != NULL) && (strcmp(mod->instr->x.str, lstName->name) == 0))	
				{
					//printf("---1 \n") ;
					lstLife = ListLife_new(cont, 1, nextPosAlive) ;
					nextPosAlive = -1 ;
				}
				// checa se está do lado direito da igualdade
				else if ((mod->instr->y.str != NULL) && (strcmp(mod->instr->y.str, lstName->name) == 0) )
				{
					//printf("---2 \n") ;
					lstLife = ListLife_new(cont, 1, nextPosAlive) ;
					nextPosAlive = cont ;		// nessa altura a variavel é usada
				}
				else if ((mod->instr->z.str != NULL) && (strcmp(mod->instr->z.str, lstName->name) == 0) )
				{
					//printf("---2 \n") ;
					lstLife = ListLife_new(cont, 1, nextPosAlive) ;
					nextPosAlive = cont ;		// nessa altura a variavel é usada					
				}
				/*else if((strcmp(mod->instr->y.str, lstName->name) == 0) || (strcmp(mod->instr->z.str, lstName->name) == 0))
				{
					printf("---2 \n") ;
					lstLife = ListLife_new(cont, 1, nextPosAlive) ;
					nextPosAlive = cont ;		// nessa altura a variavel é usada
				}*/
				else						// se nao aparece, esta morto
				{
					//printf("---3 \n") ;
					lstLife = ListLife_new(cont, 0, nextPosAlive) ;
				}
				//printf("---LSTLIFE2: %d\n", lstLife) ;
				insertListLife (lstName, lstLife) ;
				mod = mod->prev ;
				//printf("mod: %d\n", mod) ;
			}
			lstName = lstName->nextName ;
			//mod = mod->prev ;
		}
		
		lifeTab = lifeTab->next;
		printf("---NEXT LIFE TAB: %d\n", lifeTab) ;
	}
}

// ---------------- Insert Registrers --------------

void insertRegElse (Instr* ins, char** regNum, char* name, LifeTable* lifeTab, int blockLine, RegList* regs)
{

	ListName* lstName = lifeTab->firstName ;
	char* regName ;
	regName = *regNum ;			// FAZER PARA OS TRES REGS
	ListName* var = regs->firstName ;
	while(strcmp(regName, var->name)!= 0)
	{
		var = var->nextName ;
		lstName = lstName->nextName ;
	}
	ListLife* life = lstName->first ;
		while(life->posTable != blockLine)
	{
		life = life->next ;
	}
	//if(var->status == 1) 			// se a variavel está armazenada na memória
	if(true)
	{
		*regNum = name ;
	}//------------------------------------------- para as tres regs
	else if(strcmp(regName, ins->x.str) == 0)		// se a variavel é resultado da operacao
	{
		*regNum = name ;
	} //------------------------------------------- para as tres regs
	else if(life->nextPosAlive != -1)		// se nao tem proximo uso
	{
		*regNum = name ;
	} //------------------------------------------- para as tres regs
	else				// faz spill
	{
		//var->status = regs->reg1 ;		//VER!
		*regNum = name ;
	}
}

// ---------------- Insert Registrers --------------

void insertReg (Instr* ins, char* name, LifeTable* lifeTab, int blockLine, RegList* regs)
{
	//printf("entrou regs\n") ;
	ListName* lstName = lifeTab->firstName ;
	char* regName ;
	if((regs->reg1 != NULL) && (strcmp(regs->reg1, name) == 0))		// se estiver em algum registrador atuaiza
	{
		regs->reg1 = name ;
		printf("mov ebx %s \n", name) ;
	}
	else if((regs->reg2 != NULL) && (strcmp(regs->reg2, name) == 0))
	{
		regs->reg2 = name ;
		printf("mov ecx %s \n", name) ;
	}
	else if((regs->reg3 != NULL) && (strcmp(regs->reg3, name) == 0))
	{
		regs->reg3 = name ;
		printf("mov eax %s \n", name) ;
	}
	else if(regs->reg1 == NULL)		// se o registrador estiver vazio atualiza
	{
		regs->reg1 = name ;
		printf("mov ebx %s \n", name) ;
	}
	else if(regs->reg2 == NULL)
	{
		regs->reg2 = name ;
		printf("mov ecx %s \n", name) ;
	}
	else if(regs->reg3 == NULL)
	{
		regs->reg3 = name ;
		printf("mov eax %s \n", name) ;
	}
	else
	{
		printf("FAZER!\n") ;
		insertRegElse (ins, &(regs->reg1), name, lifeTab, blockLine, regs) ;
				
	}
}

// ---------------- Update Registrers --------------

void updateRegs(Instr* ins, LifeTable* lifeTab, int blockLine, RegList* regs)
{
	ListName* lstName = lifeTab->firstName ;

	while(lstName)
	{
		if((ins->y.str != NULL) && (strcmp(lstName->name, ins->y.str) == 0))		// so aloca se for uma variavel valida
		{
			insertReg (ins, ins->y.str, lifeTab, blockLine, regs) ;
			break ;
		}
		lstName = lstName->nextName ;	
	}

	lstName = lifeTab->firstName ;
	while(lstName)
	{
		if((ins->z.str != NULL) && (strcmp(lstName->name, ins->z.str) == 0))
		{
			insertReg (ins, ins->z.str, lifeTab, blockLine, regs) ;
			break ;
		}
		lstName = lstName->nextName ;	
	}

	lstName = lifeTab->firstName ;
	while(lstName)
	{
		if((ins->x.str != NULL) && (strcmp(lstName->name, ins->x.str) == 0))
		{
			insertReg (ins, ins->x.str, lifeTab, blockLine, regs) ;
			break ;
		}
		lstName = lstName->nextName ;	
	}
	
}

// -------------------- Fill Reg List ------------
void FillRegList (IR* ir)
{
	int blockLine ;
	Function* lastFn = ir->functions;
	LifeTable* lifeTab = NULL;
	RegList* regs = NULL ;
	Instr* ins = NULL ;

	while (lastFn) 
	{
		ins = lastFn->code ;
		lifeTab = ins->bBlock->life ;		//cada nova funcao é o início de uma nova tabela
		regs = lifeTab->regs ;
		blockLine = 0 ;

		//printf("NEW BLOCK! \n") ;
		int bBlock = ins->bBlock->basicNum ;
		while(ins)
		{		
			if(bBlock == (ins->bBlock->basicNum))	//while por bloco básico
			{
				updateRegs(ins, lifeTab, blockLine, regs) ;	//atualiza os registradores
				blockLine++ ;
			}
			else
			{
				bBlock = ins->bBlock->basicNum ;
				lifeTab = ins->bBlock->life ;		//cada novo bloco é o início de uma nova tabela
				regs = lifeTab->regs ;
				//printf("NEW BLOCK \n") ;
				updateRegs(ins, lifeTab, blockLine, regs) ;	//atualiza os registradores
				blockLine = 1 ;
			}

			ins = ins->next ;
		}
		lastFn = lastFn->next;
	}
	
}

// -------------------- Instr --------------------

/*
Allocate a new Instr.
This function may receive up to three extra arguments,
representing x, y and z in the three-address code representation.
*/
Instr* Instr_new(Opcode op, ...) 
{
	va_list ap;
	va_start(ap, op);
	Instr* ins = calloc(1, sizeof(Instr));
	ins->op = op;
	ins->bBlock = basicBlock_new() ;
	ins->bBlock->basicNum = basicBlock ;
	switch (op) 
	{
	// instructions with x only
		case OP_LABEL:
		{
			ins->x = va_arg(ap, Addr);
			basicBlock++ ;
			break ;
		}
		case OP_GOTO:
		{
			ins->x = va_arg(ap, Addr);
			basicBlock++ ;
			break;
		}
		case OP_PARAM:
		case OP_CALL:
		case OP_RET_VAL:
		{
			ins->x = va_arg(ap, Addr);
			break;
		}
		// instructions with x and y
		case OP_IF:
		{
			ins->x = va_arg(ap, Addr);
			ins->y = va_arg(ap, Addr);
			basicBlock++ ;
			break;
		}
		case OP_IF_FALSE:
		{
			ins->x = va_arg(ap, Addr);
			ins->y = va_arg(ap, Addr);
			basicBlock++ ;
			break;
		}
		case OP_SET:
		case OP_SET_BYTE:
		case OP_NEG:
		case OP_NEW:
		case OP_NEW_BYTE:
		{
			ins->x = va_arg(ap, Addr);
			ins->y = va_arg(ap, Addr);
			break;
		}
		// instruction with x, y and z
		case OP_SET_IDX:
		case OP_SET_IDX_BYTE:
		case OP_IDX_SET:
		case OP_IDX_SET_BYTE:
		case OP_NE:
		case OP_EQ:
		case OP_LT:
		case OP_GT:
		case OP_LE:
		case OP_GE:
		case OP_ADD:
		case OP_SUB:
		case OP_DIV:
		case OP_MUL:
		{
			ins->x = va_arg(ap, Addr);
			ins->y = va_arg(ap, Addr);
			ins->z = va_arg(ap, Addr);
			break;
		}
		// instruction with no args
		case OP_RET:
		{
			break;
		}
	}
	totalBlockLines++ ;
	va_end(ap);
	return ins;
}

/*
Output an instruction to the given file descriptor.
*/
static void Instr_dump(Instr* ins, FILE* fd) 
{
	const char* x = ins->x.str;
	const char* y = ins->y.str;
	const char* z = ins->z.str;
	const char* fmt;

	switch (ins->op) 
	{
		case OP_LABEL: 
			fmt = "%s:\n";	
			break;
		case OP_GOTO: 
			fmt = "\tgoto %s\n";	
			break;
		case OP_PARAM: 
			fmt = "\tparam %s\n";	
			break;
		case OP_CALL: 
			fmt = "\tcall %s\n";	
			break;
		case OP_IF: 
			fmt = "\tif %s goto %s\n";	
			break;
		case OP_IF_FALSE: 
			fmt = "\tifFalse %s goto %s\n";	
			break;
		case OP_SET: 
			fmt = "\t%s = %s\n";	
			break;
		case OP_SET_BYTE: 
			fmt = "\t%s = byte %s\n";	
			break;
		case OP_SET_IDX: 
			fmt = "\t%s = %s[%s]\n";	
			break;
		case OP_SET_IDX_BYTE: 
			fmt = "\t%s = byte %s[%s]\n";	
			break;
		case OP_IDX_SET: 
			fmt = "\t%s[%s] = %s\n";	
			break;
		case OP_IDX_SET_BYTE: 
			fmt = "\t%s[%s] = byte %s\n";	
			break;
		case OP_RET: 
			fmt = "\tret\n";	
			break;
		case OP_RET_VAL: 
			fmt = "\tret %s\n";	
			break;
		case OP_NE: 
			fmt = "\t%s = %s != %s\n";	
			break;
		case OP_EQ: 
			fmt = "\t%s = %s == %s\n";	
			break;
		case OP_LT: 
			fmt = "\t%s = %s < %s\n";	
			break;
		case OP_GT: 
			fmt = "\t%s = %s > %s\n";	
			break;
		case OP_LE: 
			fmt = "\t%s = %s <= %s\n";	
			break;
		case OP_GE: 
			fmt = "\t%s = %s >= %s\n";	
			break;
		case OP_ADD: 
			fmt = "\t%s = %s + %s\n";	
			break;
		case OP_SUB: 
			fmt = "\t%s = %s - %s\n";	
			break;
		case OP_DIV: 
			fmt = "\t%s = %s / %s\n";	
			break;
		case OP_MUL: 
			fmt = "\t%s = %s * %s\n";	
			break;
		case OP_NEG: 
			fmt = "\t%s = - %s\n";	
			break;
		case OP_NEW: 
			fmt = "\t%s = new %s\n";	
			break;
		case OP_NEW_BYTE: 
			fmt = "\t%s = new byte %s\n";	
			break;
	}

	fprintf(fd, "block %d\t", ins->bBlock->basicNum);
	fprintf(fd, fmt, x, y, z);
	
}

// -------------------- Function --------------------

/*
Allocate a new function, with a given name and a given set of arguments.
*/
Function* Function_new(char* name, Variable* args) 
{
	Function* fun = calloc(1, sizeof(Function));
	fun->name = name;
	fun->locals = args;
	int nArgs = 0;
	for (Variable* a = args; a; a = a->next) 
	{
		nArgs++;
	}
	fun->nArgs = nArgs;
	basicBlock = 0 ;
	totalBlockLines = 0 ;
	return fun;
}

/*
Output a function to the given file descriptor.
*/
static void Function_dump(Function* fun, FILE* fd) 
{
	fprintf(fd, "fun %s (", fun->name);
	Variable* arg = fun->locals;
	for (int i = 0; i < fun->nArgs; i++) 
	{
		if (i > 0) 
		{
			fprintf(fd, ", ");
		}
		fprintf(fd, "%s", arg->name);
		arg = arg->next;
	}
	fprintf(fd, ")\n");
	for (Instr* ins = fun->code; ins; ins = ins->next) 
	{
		Instr_dump(ins, fd);
	}
}

// -------------------- IR --------------------

/*
Allocate a new IR data structure.
*/
IR* IR_new() 
{
	IR* ir = calloc(1, sizeof(IR));
	return ir;
}

/*
Set the list of literal strings.
*/
void IR_setStrings(IR* ir, String* strings) 
{
	ir->strings = strings;
}

/*
Set the list of globals.
*/
void IR_setGlobals(IR* ir, Variable* globals)
{
	ir->globals = globals;
}

/*
Add a function to the IR data structure.
*/
void IR_addFunction(IR* ir, Function* fun) 
{
	if (!ir->functions) 
	{
		ir->functions = fun;
		return;
	}
	Function* lastFn = ir->functions;
	while (lastFn->next) 
	{
		lastFn = lastFn->next;
	}
	lastFn->next = fun;	
}


void printLifeTable(IR* ir)
{

	LifeTable* lifeTab = ir->functions->code->bBlock->life;
	ListName* lstName = lifeTab->firstName ;
	ListLife* lstLife ;
	int cont ;

	while (lifeTab)
	{
		//printf("lifetab: %d\n", lifeTab) ;
		//printf("lifeTab->firstName: %s\n", lifeTab->firstName->name) ;
		lstName = lifeTab->firstName ;
		while(lstName)
		{	
			//printf("entrou\n") ;
			printf("lstName: %s\n", lstName->name) ;
			printf("%s: \n", lstName->name) ; 
			//printf("passou\n") ;
			lstLife = lstName->first ;	
			//printf("passou2\n") ;	
			for(cont=0;cont<lifeTab->qtdLines+1;cont++)
			{
				//printf("lstLife %d\n", lstLife) ;
				printf("=>vivo: %d ; next: %d \n", lstLife->alive, lstLife->nextPosAlive) ;
				lstLife = lstLife->next ; 
				//printf("passou3\n") ;
			}
			//printf("passou4\n") ;
			lstName = lstName->nextName ;
			printf("\n") ;
		}
		
		lifeTab = lifeTab->next;
	}
}
/*
Output the entire IR data structure to the given file descriptor.
This outputs a file equivalent to the one given as input to the program.
*/
void IR_dump(IR* ir, FILE* fd) 
{
	for (String* s = ir->strings; s; s = s->next) 
	{
		fprintf(fd, "string %s = %s\n", s->name, s->value);
	}
	fprintf(fd, "\n");
	for (Variable* v = ir->globals; v; v = v->next) 
	{
		fprintf(fd, "global %s\n", v->name);
	}
	fprintf(fd, "\n");
	for (Function* fun = ir->functions; fun; fun = fun->next) 
	{
		Function_dump(fun, fd);
		fprintf(fd, "\n");
	}

	//estruta de tres enderecos formada
	//printf("lastFn bb: %d\n", fun->code->bBlock->basicNum) ;
	CreateLifeTable (ir) ;
	FillLifeTableStatus (ir) ;
	printLifeTable(ir) ;
	FillRegList (ir) ;
}
