all: build brainfuck clean

brainfuck: build
	./main

build: main.c file.c file.h
	gcc -W -Wall -std=c11 -pedantic main.c file.c -o main

clean:
	rm -rf *.o main