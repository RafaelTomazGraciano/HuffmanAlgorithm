all: run

run: HuffmanAlgorithm.o functions.o
	gcc -Wall -o run HuffmanAlgorithm.o functions.o

HuffmanAlgorithm.o: HuffmanAlgorithm.c
	gcc -c -Wall HuffmanAlgorithm.c

functions.o: functions.c
	gcc -c -Wall functions.c

clean: 
	rm HuffmanAlgorithm.o
	rm functions.o
	rm run