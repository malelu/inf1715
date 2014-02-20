lexical_analizer: lex.yy.c
	gcc -o lexical_analizer lex.yy.c

lex.yy.c: lexical_analizer.l
	flex lexical_analizer.l

clean:
	rm -f lexical_analizer *.o lex.yy.c

test: lexical_analizer
	@echo "Teste sem erros:"
	./lexical_analizer < teste_ok.txt
