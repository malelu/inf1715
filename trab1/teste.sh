#!/bin/bash

echo "Gerando arquivos de saida no diretorio saida"

for testesIn in $(ls testes/entrada)
do
		 	
	./lexico < testes/entrada/$testesIn > "testes/saida/$testesIn.out"
done

echo "Arquivos gerados"

echo "Compara os resultados do teste com o gabarito"

for saida in $(ls testes/saida)
do
	diff -q testes/gabarito/$saida.exp testes/saida/$saida
done

echo "Fim de teste."

