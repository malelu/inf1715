#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ir.h"

int basicBlock = 0 ;
int totalBlockLines ;
LifeTable* allVars = NULL;
int qtdLabel = 1 ;
char* regsCmp = NULL ;
int posVar = 0 ;

// -------------------- List --------------------

/*
Concatenate two lists. Either list may be NULL.
In that case, the other one is returned unmodified.
*/
List* List_link(List* l1, List* l2) {

	if (!l1) 
	{
		return l2;
	}
	List* last = l1;

	while (last->next) 
	{
		last = last->next;
	}
	last->next = l2;
	return l1;
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
	new_listName->status = 0 ;
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
	regs->reg4 = NULL ;
	regs->reg5 = NULL ;
	regs->reg6 = NULL ;
	return regs ;
}

//------------------Insert Info --------------

void InsertInfo(InfoStack* info, InfoStack* stack)
{
	InfoStack* stackAux = stack ;
	while(stackAux->next)
	{
		stackAux = stackAux->next ;
	}
	stackAux->next = info ;
}

//------------------Info Stack --------------

InfoStack* InfoStack_new(char* name, int pos)
{
	InfoStack* new_infoStack = calloc(1, sizeof(InfoStack));
	new_infoStack->name = name ; 
	new_infoStack->pos = pos ;
	new_infoStack->next = NULL ;
	return new_infoStack ;
}

//--------------------- Stack --------------

Stack* Stack_new()
{
	Stack* new_stack = calloc(1, sizeof(Stack));
	new_stack->stackParam = NULL ; 
	new_stack->qtdParam = 0 ;
	new_stack->stackVar = NULL ;
	new_stack->qtdVar = 0 ;
	return new_stack ;
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
	new_lifeTable->stack = NULL ;
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

bool isParam (Stack* stack, char* var)
{
	InfoStack* info = stack->stackParam ;
	while(info)
	{
		if(strcmp(info->name, var) == 0)
			return true ;
		info = info->next ;
	}
	return false ;
}
//-------------------- Inserting into life table and registrer -------

void InsertLifeTable (Instr* code, LifeTable* lifeTab, RegList* regs, Stack* stack)
{
	char* name = malloc(20) ;
	char* name2 = malloc(20) ;
	char* name3 = malloc(20) ;
	if((code->op == OP_IDX_SET) || (code->op == OP_IDX_SET_BYTE))
	{
		snprintf(name, 20, "%s[%s]", code->x.str, code->y.str);

		snprintf(name2, 20, "%s", code->z.str);		//lado direito da igualdade => pode nao ser uma variavel
		if(!notRepeated(name2, allVars))		//se é uma variável válida
		{
			if(notRepeated(name2, lifeTab))
			{
				InsertListName (name2, lifeTab) ;
				InsertRegsListName (name2, regs) ;
				lifeTab->qtdNames = lifeTab->qtdNames + 1 ;


				if(!isParam(stack, name2))		// insere na pilha de variaveis
				{
					InfoStack* info = InfoStack_new(name2, posVar) ;
					InsertInfo(stack->stackVar, info) ;
					stack->qtdVar++ ;
					posVar++ ;
				}
			}
		}
	}
	else if((code->op == OP_SET_IDX) || (code->op == OP_SET_IDX_BYTE))
	{
		snprintf(name, 20, "%s[%s]", code->y.str, code->z.str);	//lado direito da igualdade => garantidamente variavel

		snprintf(name2, 20, "%s", code->x.str);

		if(notRepeated(name2, lifeTab))
		{
			InsertListName (name2, lifeTab) ;
			InsertRegsListName (name2, regs) ;
			InsertListName (name2, allVars) ;
			lifeTab->qtdNames = lifeTab->qtdNames + 1 ;

			if(!isParam(stack, name2))		// insere na pilha de variaveis
			{
				InfoStack* info = InfoStack_new(name2, posVar) ;
				InsertInfo(stack->stackVar, info) ;
				stack->qtdVar++ ;
				posVar++ ;
			}
		}
		
	}
	else
	{
		strcpy(name, code->x.str) ;
		snprintf(name2, 20, "%s", code->y.str);		//lado direito da igualdade => pode nao ser uma variavel
		if(!notRepeated(name2, allVars))		//se é uma variável válida
		{
			if(notRepeated(name2, lifeTab))
			{
				InsertListName (name2, lifeTab) ;
				InsertRegsListName (name2, regs) ;
				lifeTab->qtdNames = lifeTab->qtdNames + 1 ;

				if(!isParam(stack, name2))		// insere na pilha de variaveis
				{
					InfoStack* info = InfoStack_new(name2, posVar) ;
					InsertInfo(stack->stackVar, info) ;
					stack->qtdVar++ ;
					posVar++ ;
				}
			}
		}
		snprintf(name3, 20, "%s", code->z.str);		//lado direito da igualdade => pode nao ser uma variavel
		if(!notRepeated(name3, allVars))		//se é uma variável válida
		{
			if(notRepeated(name3, lifeTab))
			{
				InsertListName (name3, lifeTab) ;
				InsertRegsListName (name3, regs) ;
				lifeTab->qtdNames = lifeTab->qtdNames + 1 ;

				if(!isParam(stack, name3))		// insere na pilha de variaveis
				{
					InfoStack* info = InfoStack_new(name3, posVar) ;
					InsertInfo(stack->stackVar, info) ;
					stack->qtdVar++ ;
					posVar++ ;
				}
			}
		}	
	}
		
	if(notRepeated(name, lifeTab))
	{
		//printf("name: %s\n", name) ;
		InsertListName (name, lifeTab) ;
		InsertListName (name, allVars) ;
		InsertRegsListName (name, regs) ;
		lifeTab->qtdNames = lifeTab->qtdNames + 1 ;

		if(!isParam(stack, name))		// insere na pilha de variaveis
		{
			InfoStack* info = InfoStack_new(name, posVar) ;
			InsertInfo(stack->stackVar, info) ;
			stack->qtdVar++ ;
			posVar++ ;
		}
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
	Variable* args ;
	Stack* stack ;

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

		stack = Stack_new() ;			// a cada nova funcao cria uma pilha
		lifeTab->stack = stack ;
		args = lastFn->locals;			// Insere os parametros na pilha
		for (int i = 0; i < lastFn->nArgs; i++) 
		{
			InfoStack* info = InfoStack_new(args->name, i) ; 
			InsertInfo(stack->stackParam, info) ;
			stack->qtdParam++ ;
			//printf("=======================%s\n", args->name);
			//printf("=====%d\n", stack->qtdParam);
			args = args->next;
		}
		
		posVar = 0 ;
		while(ins)
		{			
			if(validVariable(ins))
			{
				if(bBlock == (ins->bBlock->basicNum))	//while por bloco básico
				{
					InsertLifeTable(ins, lifeTab, regs, stack) ;		// insere na tabela de registradores a nova variável
					//printf("ins %d\n", ins) ;
				}
				else
				{
					bBlock = ins->bBlock->basicNum ;
					prevTable = lifeTab;
					lifeTab = lifeTable_new() ;		//cada novo bloco é o início de uma nova tabela
					regs = regList_new() ;
					lifeTab->regs = regs ;
					lifeTab->stack = stack ;
					prevTable->next = lifeTab ;
					printf("NEW BLOCK2 \n") ;
					InsertLifeTable(ins, lifeTab, regs, stack) ;
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
	char* name = " ";

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
		/*while(mod)
		{
			printf("====mod//->instr->x.str %s\n", mod->instr->x.str) ;
			mod = mod->prev ;
		}
		mod =  lifeTab->lastInstructions ;*/
		//-------------------------------------------	
	
			for(cont=lifeTab->qtdLines-1;cont>=0;cont--)
			{//printf("---0 \n") ;
				//printf("--mod//->instr->x.str %s\n", mod->instr->x.str) ;


				/*if((mod->instr->op == OP_IDX_SET) || (mod->instr->op == OP_IDX_SET_BYTE))
				{
					printf("entrou\n") ;
					printf("mod->instr->x.str: %d\n", mod->instr->x.str) ;
					printf("mod->instr->y.str: %d\n", mod->instr->y.str) ;
					snprintf(name, 20, "%s[%s]", mod->instr->x.str, mod->instr->y.str);
					printf("saiu\n") ;
				}

				// checa se vetor está do lado esquerdo da igualdade
				if((mod->instr->x.str != NULL) && (mod->instr->y.str != NULL) && (name != ' ' ))
				{
					if(strcmp(name, lstName->name) == 0)
					{
						//printf("---1 \n") ;
						lstLife = ListLife_new(cont, 1, nextPosAlive) ;
						nextPosAlive = -1 ;
					}
				}*/
				// checa se está do lado esquerdo da igualdade
				if((mod->instr->x.str != NULL) && (strcmp(mod->instr->x.str, lstName->name) == 0))	
				{
					//printf("---1 \n") ;
					if((mod->instr->op == OP_IDX_SET) || (mod->instr->op == OP_IDX_SET_BYTE))
					{
						lstLife = ListLife_new(cont, 0, nextPosAlive) ;
					}
					else
					{
						lstLife = ListLife_new(cont, 1, nextPosAlive) ;
						nextPosAlive = -1 ;
					}
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
		}
		
		lifeTab = lifeTab->next;
		printf("---NEXT LIFE TAB: %d\n", lifeTab) ;
	}
}

// ---------------- Make Spill --------------

int makeSpill(LifeTable* lifeTab, char* name)
{
	Stack* stack = lifeTab->stack ;
	InfoStack * info = stack->stackParam ;

	while(info)
	{
		if(strcmp(info->name, name)==0)
		{
			int pos ;
			pos = 4*(info->pos) + 8 ;
			printf("\tmovl %%ebx, %d(%%ebp)\n", pos) ;
			return 1 ;
		}
		info = info->next ;
	}

	info = stack->stackVar ;		// se a variavel nao eh parametro
	while(info)
	{
		if(strcmp(info->name, name)==0)
		{
			int pos ;
			pos = -4*(info->pos) -4 ;
			printf("\tmovl %%ebx, %d(%%ebp)\n", pos) ;
			return 1 ;
		}
		info = info->next ;
	}
}
// ---------------- Future Life --------------

ListLife* FutureLife (ListName* varLifeTab, int blockLine) 
{
	ListLife* life = varLifeTab->first ;				// ve a vida futura de cada variavel
	while(life->posTable != blockLine)
	{
		life = life->next ;
	}
	return life ;
}

// ---------------- Get Name --------------

ListName* getLstName (char* regName, ListName* var)
{

	while(strcmp(regName, var->name)!= 0)
	{
		var = var->nextName ;
	}
	return var ;
}

// ---------------- Insert eax --------------

char* insertRegElseEax (Instr* ins, char* name, LifeTable* lifeTab, int blockLine, RegList* regs)
{
	ListName* var3 = getLstName (regs->reg3, regs->firstName) ;
	ListName* varLifeTab3 = getLstName (regs->reg3, lifeTab->firstName) ;

	ListLife* life3 =  FutureLife(varLifeTab3, blockLine) ;	// ve a vida futura de cada variavel

	if(var3->status == 1) 		// se a variavel está armazenada na memória	
	{
		regs->reg3 = name ;
		printf("\tmovl %s, \%%eax \n", name) ;
		return "eax" ;
	}	
	else if(strcmp(regs->reg3, ins->x.str) == 0)	// se a variavel é resultado da operacao
	{
		regs->reg3 = name ;
		printf("\tmovl %s, %%eax \n", name) ;
		return "eax" ;
	}
	else if(life3->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg3 = name ;
		printf("\tmovl %s, %%eax \n", name) ;
		return "eax" ;
	}
	else				// faz spill
	{
		var3->status = 1 ;		//VER!
		regs->reg3 = name ;
		printf("SPILL\n") ;
		makeSpill(lifeTab, regs->reg3) ;
		printf("\tmovl %s, %%eax \n", name) ;
		return "eax" ;
	}
}



// ---------------- Insert Registrers --------------

char* insertRegElse (Instr* ins, char* name, LifeTable* lifeTab, int blockLine, RegList* regs)
{
// reg1 = ebx ; reg2 = ecx ; reg3 = eax ; reg4 = edx ; reg5 = edi ; reg6 = esi
			
	ListName* var1 = getLstName(regs->reg1, regs->firstName) ;		//acha as variaveis de cada reg na lifetable
	ListName* varLifeTab1 = getLstName(regs->reg1, lifeTab->firstName) ;

	ListName* var2 = getLstName(regs->reg2, regs->firstName) ;
	ListName* varLifeTab2 = getLstName(regs->reg2, lifeTab->firstName) ;

	ListName* var4 = getLstName(regs->reg4, regs->firstName) ;
	ListName* varLifeTab4 = getLstName(regs->reg4, lifeTab->firstName) ;

	ListName* var5 = getLstName(regs->reg5, regs->firstName) ;
	ListName* varLifeTab5 = getLstName(regs->reg5, lifeTab->firstName) ;

	ListName* var6 = getLstName(regs->reg6, regs->firstName) ;
	ListName* varLifeTab6 = getLstName(regs->reg6, lifeTab->firstName) ;

	ListLife* life1 = FutureLife(varLifeTab1, blockLine) ;	// ve a vida futura de cada variavel
	ListLife* life2 = FutureLife(varLifeTab2, blockLine) ;
	ListLife* life4 = FutureLife(varLifeTab4, blockLine) ;
	ListLife* life5 = FutureLife(varLifeTab5, blockLine) ;
	ListLife* life6 = FutureLife(varLifeTab6, blockLine) ;

	//printf("var1: %d\n", var1) ;

	if(var1->status == 1) 			// se a variavel está armazenada na memória
	{
		regs->reg1 = name ;
		printf("\tmovl %s, %%ebx \n", name) ;
		return "ebx" ;
	}
	else if(var2->status == 1) 			
	{
		regs->reg2 = name ;
		printf("\tmovl %s, %%ecx \n", name) ;
		return "ecx" ;
	}
	else if(var4->status == 1) 			
	{
		regs->reg4 = name ;
		printf("\tmovl %s, %%edx \n", name) ;
		return "edx" ;
	}
	else if(var5->status == 1) 			
	{
		regs->reg5 = name ;
		printf("\tmovl %s, %%edi \n", name) ;
		return "edi" ;
	}
	else if(var6->status == 1) 			
	{
		regs->reg6 = name ;
		printf("\tmovl %s, %%esi \n", name) ;
		return "esi" ;
	}
	else if(strcmp(regs->reg1, ins->x.str) == 0)		// se a variavel é resultado da operacao
	{
		regs->reg1 = name ;
		printf("\tmovl %s, %%ebx \n", name) ;
		return "ebx" ;
	}
	else if(strcmp(regs->reg2, ins->x.str) == 0)		
	{
		regs->reg2 = name ;
		printf("\tmovl %s, %%ecx \n", name) ;
		return "ecx" ;
	}
	else if(strcmp(regs->reg4, ins->x.str) == 0)	
	{
		regs->reg4 = name ;
		printf("\tmovl %s, %%edx \n", name) ;
		return "edx" ;
	}
	else if(strcmp(regs->reg5, ins->x.str) == 0)	
	{
		regs->reg5 = name ;
		printf("\tmovl %s, %%edi \n", name) ;
		return "edi" ;
	}
	else if(strcmp(regs->reg6, ins->x.str) == 0)	
	{
		regs->reg6 = name ;
		printf("\tmovl %s, %%esi \n", name) ;
		return "esi" ;
	}
	else if(life1->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg1 = name ;
		printf("\tmovl %s, %%ebx \n", name) ;
		return "ebx" ;
	}
	else if(life2->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg2 = name ;
		printf("\tmovl %s, %%ecx \n", name) ;
		return "ecx" ;
	}
	else if(life4->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg4 = name ;
		printf("\tmovl %s, %%edx \n", name) ;
		return "edx" ;
	}
	else if(life5->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg5 = name ;
		printf("\tmovl %s, %%edi \n", name) ;
		return "edi" ;
	}
	else if(life6->nextPosAlive != -1)		// se nao tem proximo uso
	{
		regs->reg6 = name ;
		printf("\tmovl %s, %%esi \n", name) ;
		return "esi" ;
	}
	else				// faz spill
	{
		var1->status = 1 ;		//VER!
		regs->reg1 = name ;
		printf("SPILL\n") ;
		makeSpill(lifeTab, regs->reg1) ;
		return "ebx" ;
	}
}

// ---------------- Insert Registrers --------------

char* insertReg (Instr* ins, char* name, LifeTable* lifeTab, int blockLine, RegList* regs, int varOrder, int ret)  //ret = 1 se eh retorno
{
//printf("entrou\n") ;
	if( ret == 1)			// mexer apenas no reg3 -> eax
	{
		//printf("entrou\n") ;
		if((regs->reg3 != NULL) && (strcmp(regs->reg3, name) == 0))
		{
			//printf("entrou1\n") ;
			regs->reg3 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%eax \n", name) ;
			}
			return "eax" ;
		}
		else if(regs->reg3 == NULL)
		{
			//printf("entrou2\n") ;
			regs->reg3 = name ;
			printf("\tmovl %s, %%eax \n", name) ;
			return "eax" ;
		}
		else
		{
			return insertRegElseEax (ins, name, lifeTab, blockLine, regs) ;
		}
	}
	
	else
	{
		//printf("entrou regs\n") ;
		if((regs->reg1 != NULL) && (strcmp(regs->reg1, name) == 0))		// se estiver em algum registrador atualiza
		{
			regs->reg1 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%ebx \n", name) ;
			}
			return "ebx" ;
		}
		else if((regs->reg2 != NULL) && (strcmp(regs->reg2, name) == 0))
		{
			regs->reg2 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%ecx \n", name) ;
			}
			return "ecx" ;
		}
		else if((regs->reg4 != NULL) && (strcmp(regs->reg4, name) == 0))
		{
			regs->reg4 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%edx \n", name) ;
			}
			return "edx" ;
		}
		else if((regs->reg5 != NULL) && (strcmp(regs->reg5, name) == 0))
		{
			regs->reg5 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%edi \n", name) ;
			}
			return "edi" ;
		}
		else if((regs->reg6 != NULL) && (strcmp(regs->reg6, name) == 0))
		{
			regs->reg6 = name ;
			if(varOrder == 1)		// se for x, precisa alocar
			{
				printf("\tmovl %s, %%esi \n", name) ;
			}
			return "esi" ;
		}
		else if(regs->reg1 == NULL)		// se o registrador estiver vazio atualiza
		{
			regs->reg1 = name ;
			printf("\tmovl %s, %%ebx \n", name) ;
			return "ebx" ;
		}
		else if(regs->reg2 == NULL)
		{
			regs->reg2 = name ;
			printf("\tmovl %s, %%ecx \n", name) ;
			return "ecx" ;
		}
		else if(regs->reg4 == NULL)		
		{
			regs->reg4 = name ;
			printf("\tmovl %s, %%edx \n", name) ;
			return "edx" ;
		}
		else if(regs->reg5 == NULL)
		{
			regs->reg5 = name ;
			printf("\tmovl %s, %%edi \n", name) ;
			return "edi" ;
		}
		else if(regs->reg6 == NULL)
		{
			regs->reg6 = name ;
			printf("\tmovl %s, %%esi \n", name) ;
			return "esi" ;
		}
		else
		{
			printf("FAZER!1\n") ;
			return insertRegElse (ins, name, lifeTab, blockLine, regs) ;
				
		}
	}
}

// ---------------- Print Operations --------------------
void printOperation(int op, char* regstr1, char* regstr2)
{
	switch(op)
	{
		case OP_ADD:
			printf("\taddl ") ;
			break ;
		case OP_SUB:
			printf("\tsubl ") ;
			break ;
		case OP_MUL:
			printf("\timull ") ;
			break ;
		default:
			printf("\tcmpl ") ;
			break ;	
	}

	if((strcmp(regstr1, "ebx") == 0) || (strcmp(regstr1, "ecx") == 0) || (strcmp(regstr1, "eax") == 0) ||
		(strcmp(regstr1, "edx") == 0) || (strcmp(regstr1, "edi") == 0) || (strcmp(regstr1, "esi") == 0))
	{	
		printf("%%%s, ", regstr1) ;
	}
	else
		printf("%s, ", regstr1) ;


	if((strcmp(regstr2, "ebx") == 0) || (strcmp(regstr2, "ecx") == 0) || (strcmp(regstr2, "eax") == 0) ||
		(strcmp(regstr2, "edx") == 0) || (strcmp(regstr2, "edi") == 0) || (strcmp(regstr2, "esi") == 0))
	{	
		printf("%%%s\n", regstr2) ;
	}
	else
		printf("%s\n", regstr2) ;

}

// ---------------- Search Var In Registrers --------------

char* searchVarInReg(char* name, RegList* regs)
{
	if((regs->reg1 != NULL) && (strcmp(regs->reg1, name) == 0))
		return "ebx" ;
	else if((regs->reg2 != NULL) && (strcmp(regs->reg2, name) == 0))
		return "ecx" ;
	else if((regs->reg3 != NULL) && (strcmp(regs->reg3, name) == 0))
		return "eax" ;
	else
		return NULL ;
}

// ---------------- Search Insert Registrers --------------
char* searchInsert (Instr* ins, char* var, LifeTable* lifeTab, int blockLine, RegList* regs, int varOrder, int ret) //varOrder = 1 -> x
{

	if (notRepeated(var, allVars))		// eh um numero
	{
		if( ret == 1)
		{
			printf("\tmovl $%s, %%eax\n", var) ;
			return "eax" ;
		}
		return insertReg (ins, var, lifeTab, blockLine, regs, varOrder, ret) ;
	}
	//printf("var: %s\n", var) ;
	ListName* lstName = lifeTab->firstName ;
	while(lstName)
	{
		//printf("OI\n") ;
		//if(lstName != NULL)
		 	//printf("---%s\n", lstName->name) ;
		if((var != NULL) && (strcmp(lstName->name, var) == 0))		// so aloca se for uma variavel valida
		{
			return insertReg (ins, var, lifeTab, blockLine, regs, varOrder, ret) ;
		}
		lstName = lstName->nextName ;	
		//printf("%d\n", lstName) ;
	}
}

// ---------------- Search Insert Number In Registrers --------------
char* searchInsertNumber (Instr* ins, char* var, LifeTable* lifeTab, int blockLine, RegList* regs, int varOrder, int ret) //varOrder = 1 -> x
{

	return insertReg (ins, var, lifeTab, blockLine, regs, varOrder, ret) ;

}

// ---------------- insert Var Regs --------------

void insertVarReg(char* var, char* regstr, RegList* regs)
{
	//printf("oi2\n") ;
	//printf("regstr: %s\n", regstr) ;
	//printf("regs->reg1: %s\n", regs->reg1) ;
	
	if(strcmp(regstr, "ebx") == 0)
	{	
		regs->reg1 = var ;
	}
	else if(strcmp(regstr, "ecx") == 0)
	{
		regs->reg2 = var ;
	}
	else if(strcmp(regstr, "eax") == 0)
	{
		regs->reg3 = var ;
	}
	else if(strcmp(regstr, "edx") == 0)
	{
		regs->reg4 = var ;
	}
	else if(strcmp(regstr, "edi") == 0)
	{
		regs->reg5 = var ;
	}
	else
	{
		regs->reg6 = var ;
	}
}

// ---------------- Update Registrers --------------

void updateRegs(Instr* ins, LifeTable* lifeTab, int blockLine, RegList* regs)
{
	ListName* lstName = lifeTab->firstName ;
	char* regstr1 = malloc(20);
	char* regstr2 = malloc(20) ;
	char* regstr3 = malloc(20) ;
	char* var = NULL ;
	char* label1 = malloc(20);
	char* label2 = malloc(20);

	switch(ins->op)
	{
		case OP_RET:
			printf("\tmovl %%ebp, %%esp\n") ;
			printf("\tpopl %%ebp\n") ;
			printf("\tret\n") ;
			break ;		
		case OP_RET_VAL: 
			printf("\tmovl %%ebp, %%esp\n") ;
			printf("\tpopl %%ebp\n") ;
			regstr1 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 1, 1) ;
			printf("\tret\n") ;	
			break;
		case OP_GOTO:
			printf("\tjmp %s\n", ins->x.str) ;
			break ;
		case OP_LABEL:
			printf("%s: \n", ins->x.str) ;
			break ;
		case OP_PARAM: 
			var = searchVarInReg(ins->x.str, regs) ;
			printf("\tpush %s\n", var) ;
			break;
		case OP_CALL: 
			printf("\tcall %s\n", ins->x.str) ;
			//salvar retorno
			printf("\tpop %%edx\n") ;
			printf("\tpop %%ecx\n") ;
			printf("\tpop %%eax\n") ;
			if(var != NULL)
				printf("\tPOP %s\n", var) ;
			break;
		case OP_IF: 
			printf("\tcmpl %s, $1\n", regsCmp) ;
			printf("\tjmp %s\n", ins->y.str) ;	
			break;
		case OP_IF_FALSE: 
			printf("\tcmpl %s, $0\n", regsCmp) ;
			printf("\tjmp %s\n", ins->y.str) ;	
			break;
		case OP_SET: 
			{
				regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				insertVarReg(ins->x.str, regstr1, regs) ;
				break ;
			}
		case OP_SET_BYTE: 
			{
			//fmt = "\t%s = byte %s\n";	
			break;
			}
		case OP_SET_IDX:
			{ 
			//fmt = "\t%s = %s[%s]\n";	
			break;
			}
		case OP_SET_IDX_BYTE: 
			{
			//fmt = "\t%s = byte %s[%s]\n";	
			break;
			}
		case OP_IDX_SET: 
			{
				regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				printf("\timul $4, %%%s\n", regstr1) ;
			//fmt = "\t%s[%s] = %s\n";	
			break;
			}
		case OP_IDX_SET_BYTE: 
			{
				regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
			//fmt = "\t%s[%s] = byte %s\n";	
			break;
			}
		case OP_NE: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;
				
				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjne %s\n", label1); 			
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_EQ: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;

				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tje %s\n", label1); 			
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;		
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_LT: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;

				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjl %s\n", label1); 
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_GT: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;

				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjg %s\n", label1); 			
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_LE: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;

				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjle %s\n", label1); 			
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_GE: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
				}
				else
					snprintf(regstr1, 20, "$%s", ins->y.str);

				if (!notRepeated(ins->z.str, lifeTab))
				{
					regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				}
				else
					snprintf(regstr2, 20, "$%s", ins->z.str);

				printOperation(0, regstr1, regstr2) ;

				snprintf(label1, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjge %s\n", label1); 			
				regstr3 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tmovl $0, %%%s\n", regstr3);
				snprintf(label2, 20, ".L%d", qtdLabel);
				qtdLabel++ ;
				printf("\tjmp %s\n", label2);
				printf("%s:\n", label1) ;
				printf("\tmovl $1, %%%s\n", regstr3);
				printf("%s:\n", label2) ;
				strcpy(regsCmp, regstr3) ;
				break ;
			}
		case OP_ADD: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_ADD, regstr1, regstr2) ;
					}
					else
					{
						snprintf(regstr2, 20, "$%s", ins->z.str);
						printOperation(OP_ADD, regstr2, regstr1) ;   //mudar o registrador
					}
				}
				else
				{
					snprintf(regstr1, 20, "$%s", ins->y.str);

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_ADD, regstr1, regstr2) ;
					}
					else
					{
						regstr2 = searchInsertNumber (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_ADD, regstr1, regstr2) ;
						insertVarReg(ins->x.str, regstr2, regs) ;
					}
				}
				
				break;
			}			
		case OP_SUB: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_SUB, regstr1, regstr2) ;
					}
					else
					{
						snprintf(regstr2, 20, "$%s", ins->z.str);
						printOperation(OP_SUB, regstr2, regstr1) ;   //mudar o registrador
					}
				}
				else
				{
					snprintf(regstr1, 20, "$%s", ins->y.str);

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_SUB, regstr1, regstr2) ;
					}
					else
					{
						regstr2 = searchInsertNumber (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_SUB, regstr1, regstr2) ;
						insertVarReg(ins->x.str, regstr2, regs) ;
					}
				}
				break;
			}
		case OP_DIV: 
			{
				regstr2 = searchInsertNumber (ins, ins->y.str, lifeTab, blockLine, regs, 2, 1) ; //armazena y em eax
				regstr1 = searchInsertNumber (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
				printf("\tidivl %%%s\n", regstr1) ;
				insertVarReg(ins->x.str, "eax", regs) ;
				//regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs) ;
				//regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs) ;
				//printf("\tIDIV\n") ;
				//break;
			}
		case OP_MUL: 
			{
				if (!notRepeated(ins->y.str, lifeTab))
				{
					regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_MUL, regstr1, regstr2) ;
					}
					else
					{
						snprintf(regstr2, 20, "$%s", ins->z.str);
						printOperation(OP_MUL, regstr2, regstr1) ;   //mudar o registrador
					}
				}
				else
				{
					snprintf(regstr1, 20, "$%s", ins->y.str);

					if (!notRepeated(ins->z.str, lifeTab))
					{
						regstr2 = searchInsert (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_MUL, regstr1, regstr2) ;
					}
					else
					{
						regstr2 = searchInsertNumber (ins, ins->z.str, lifeTab, blockLine, regs, 3, 0) ;
						printOperation(OP_MUL, regstr1, regstr2) ;
						insertVarReg(ins->x.str, regstr2, regs) ;
					}
				}
				break;
			}
		case OP_NEG: 
			{
			regstr1 = searchInsert (ins, ins->y.str, lifeTab, blockLine, regs, 2, 0) ;
			printf("\timul $-1, %%%s\n", regstr1) ;
			insertVarReg(ins->x.str, regstr1, regs) ;
			break;
			}
		case OP_NEW: 
			{
			int num = atoi(ins->y.str); 
			printf("\tpushl %d\n", num*4) ;
			printf("\tcall malloc\n") ;	
			regstr1 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 1, 1) ;
			break;
			}
		case OP_NEW_BYTE: 	
			printf("\tpush %s\n", ins->y.str) ;
			printf("\tcall malloc\n") ;
			regstr1 = searchInsert (ins, ins->x.str, lifeTab, blockLine, regs, 1, 1) ;
			break;
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
	String* s = NULL;
	Variable* v = NULL ;
	regsCmp = malloc(20) ;
	Stack* stack ;
	int vars ;

	printf(".data\n") ;
	for (s = ir->strings; s; s = s->next) 
	{
		printf("%s string %s\n", s->name, s->value);
	}

	for (v = ir->globals; v; v = v->next) 
	{
		printf("%s:\n", v->name);
	}

	printf(".text\n") ;
	while (lastFn) 
	{

		ins = lastFn->code ;
		lifeTab = ins->bBlock->life ;		//cada nova funcao é o início de uma nova tabela
		regs = lifeTab->regs ;
		blockLine = 0 ;
		stack = lifeTab->stack ;

		printf("%s:\n", lastFn->name) ;
		printf("\tpush %%ebp\n") ;
		printf("\tmovl %%esp, %%ebp\n") ; 
		vars = 4*(stack->qtdVar) ;
		printf("\tsubl $%d, %%esp\n", vars) ;		

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
			qtdLabel++ ;
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
	allVars = lifeTable_new();
	CreateLifeTable (ir) ;
	FillLifeTableStatus (ir) ;
	printLifeTable(ir) ;
	FillRegList (ir) ;
}
