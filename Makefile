CC=gcc
all: src/demo.c array.o
	$(CC) -g -Wall -O2 src/demo.c array.o -o demo
array.o: src/array.c
	$(CC) -c -g -Wall -O3 src/array.c -o array.o
clean:
	rm array.o
	rm demo
