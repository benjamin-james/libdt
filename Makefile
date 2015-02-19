CC=gcc
CFLAGS=-c -g -Wall -O3

all: src/array.c
	$(CC) $(CFLAGS) src/array.c -o array.o 
clean:
	rm array.o
