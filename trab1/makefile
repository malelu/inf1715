############### Makefile ########################
all: lexico
lexico : analisadorLexico.o main.c
	gcc -o lexico analisadorLexico.o main.c analisadorLexico.h -ll

analisadorLexico.o : analisadorLexico.c
	gcc -c -o analisadorLexico.o analisadorLexico.c

analisadorLexico.c : analisadorLexico.l
	lex -t analisadorLexico.l > analisadorLexico.c 

clean: 
	rm -rf *.o 
mrproper: clean 
	rm -rf lexico
