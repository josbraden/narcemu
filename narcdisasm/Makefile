narcdisasm: main.o readfile.o displaynum.o stack.o
	gcc -static -o narcdisasm main.o readfile.o displaynum.o stack.o
main.o: main.c
	gcc -Wall -c -o main.o main.c
readfile.o: readfile.c
	gcc -Wall -c -o readfile.o readfile.c
displaynum.o: displaynum.c
	gcc -Wall -c -o displaynum.o displaynum.c
stack.o: stack.c
	gcc -Wall -c -o stack.o stack.c
clean:
	-rm -f narcdisasm *.o
