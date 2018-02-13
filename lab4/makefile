all: main

main: main.o util.o
	gcc main.o util.o -o main -lm

main.o: main.c
	gcc -c main.c -o main.o

util.o: util.c
	gcc -c util.c -o util.o

clean:
	rm *.o main
