narcasm: main.o narcasm.o narcasm.yy.o symtab.o
	gcc -static -o narcasm main.o narcasm.o symtab.o narcasm.yy.o -lfl
objects:
	make main.o
	make narcasm.o
	make narcasm.yy.o
	make symtab.o
main.o: main.c
	gcc -Wall -c -o main.o main.c
narcasm.o: narcasm.c
	gcc -Wall -c -o narcasm.o narcasm.c
symtab.o: symtab.c
	gcc -Wall -c -o symtab.o symtab.c
narcasm.yy.o: narcasm.l
	flex -o narcasm.yy.c narcasm.l
	gcc -c -o narcasm.yy.o narcasm.yy.c
# Temp target for this branch
bigbison: narcasm.l narcasm.y
	flex -o narcasm.yy.c narcasm.l
	bison -d narcasm.y
	gcc -o narcasm narcasm.tab.c narcasm.yy.c
clean:
	-rm -f narcasm main.o narcasm.o symtab.o narcasm.yy.o narcasm.yy.c
