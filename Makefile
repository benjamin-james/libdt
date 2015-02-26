CC=gcc
CFLAGS=-g -Wall -march=native
all: src/demo.c array.o
	$(CC) $(CFLAGS) -O2 src/demo.c array.o -o demo
array.o: src/array.c
	$(CC) $(CFLAGS) -c -O3 src/array.c -o array.o
clean:
	rm array.o
	rm demo
