############### Makefile ########################
all: programa

programa: analisadorSintatico.o analisadorLexico.o ast.o main.c
	gcc -o programa analisadorSintatico.o analisadorLexico.o ast.o main.c -ll -ly

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
