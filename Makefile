all: Labwork1.c Labwork1

Labwork1: Labwork1.o
	clang Labwork1.o -o Labwork1

Labwork1.o: Labwork1.c
	clang -c Labwork1.c

clean:
	rm -f *.o
