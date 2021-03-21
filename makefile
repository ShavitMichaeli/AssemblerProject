all: analyze.o	utils.o	datatable.o	symbolstable.o	wordstable.o main.o
	gcc -g analyze.o utils.o datatable.o symbolstable.o wordstable.o main.o -o assembler

analyze.o: analyze.c
	gcc -g -c -Wall -ansi -pedantic analyze.c 

utils.o: utils.c
	gcc -g -c -Wall -ansi -pedantic utils.c -lm

datatable.o: datatable.c
	gcc -g -c -Wall -ansi -pedantic datatable.c 

symbolstable.o: symbolstable.c
	gcc -g -c -Wall -ansi -pedantic symbolstable.c

wordstable.o: wordstable.c
	gcc -g -c -Wall -ansi -pedantic wordstable.c

main.o: main.c
	gcc -g -c -Wall -ansi -pedantic main.c