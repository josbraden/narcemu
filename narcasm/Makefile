narcasm: main.o narcasm.o narcasm.yy.o
	make objects
	gcc -static -o narcasm main.o narcasm.o narcasm.yy.o -lfl
objects:
	make main.o
	make narcasm.o
	make narcasm.yy.o
main.o: main.c
	gcc -Wall -c -o main.o main.c
narcasm.o: narcasm.c narcasm.h
	gcc -Wall -c -o narcasm.o narcasm.c
narcasm.yy.o: narcasm.l narcasm.h
	flex -o narcasm.yy.c narcasm.l
	gcc -c -o narcasm.yy.o narcasm.yy.c
clean:
	rm narcasm main.o narcasm.o narcasm.yy.o narcasm.yy.c
