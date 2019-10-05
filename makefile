index:
	gcc -c arvore.c
	gcc -c huffman.c
	gcc -c fila.c
	gcc main.c arvore.o huffman.o fila.o -lm -o exec
compila_executa:
	gcc -c arvore.c
	gcc -c huffman.c
	gcc -c fila.c
	gcc main.c arvore.o huffman.o fila.o -lm -o exec
	./exec entrada.txt saida.txt
clear:
	rm *.o
	rm exec
