############### Makefile ########################
all: programa

programa: analisadorSintatico.o analisadorLexico.o ast.o tabela_simbolos.o simbolos.o ir.o main.c
	gcc -Wall -o programa analisadorSintatico.o analisadorLexico.o ast.o tabela_simbolos.o simbolos.o ir.o main.c -ll -ly

ir.o : ir.c
	gcc -c ir.c

simbolos.o : simbolos.c
	gcc -c simbolos.c

tabela_simbolos.o : tabela_simbolos.c
	gcc -c tabela_simbolos.c

ast.o : ast.c
	gcc -c ast.c

analisadorSintatico.o : y.tab.c
	gcc -c -o analisadorSintatico.o y.tab.c

y.tab.c : analisadorSintatico.y
	yacc -t -y -d analisadorSintatico.y

analisadorLexico.o : analisadorLexico.c
	gcc -c -o analisadorLexico.o analisadorLexico.c

analisadorLexico.c : analisadorLexico.l
	lex -t analisadorLexico.l > analisadorLexico.c 

clean: 
	rm -rf *.o 
mrproper: clean 
	rm -rf programa
