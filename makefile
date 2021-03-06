
main3: main3.o util.o
	gcc -o main main3.o util.o -lm

main3.o: main3.c 
	gcc -c -o main3.o main3.c

main2: main2.o util.o
	gcc -o main main2.o util.o -lm

main2.o: main2.c
	gcc -c -o main2.o main2.c

main1: main1.o util.o
	gcc -o main main1.o util.o

util.o: util.c util.h
	gcc -c -o util.o util.c

main1.o: main1.c 
	gcc -c  -o main1.o main1.c

clean:
	rm *.o main
