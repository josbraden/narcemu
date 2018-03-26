narcemu: main.o machine.o
	gcc -static -o narcemu main.o machine.o
main.o: main.c narcemu.h
	gcc -Wall -c -o main.o main.c
machine.o: machine.c machine.h
	gcc -Wall -c -o machine.o machine.c
clean:
	rm narcemu machine.o main.o
