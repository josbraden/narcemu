narcasm: main.o narcasm.o
	gcc -static -o narcasm main.o narcasm.o
objects:
	make main.o
	make narcasm.o
main.o: main.c
	gcc -Wall -c -o main.o main.c
narcasm.o: narcasm.c narcasm.h
	gcc -Wall -c -o narcasm.o narcasm.c
clean:
	rm narcasm main.o narcasm.o
