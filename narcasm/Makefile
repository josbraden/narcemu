narcasm: symtab.o narcasm.yy.o narcasm.tab.o
	gcc -o narcasm symtab.o narcasm.yy.o narcasm.tab.o
symtab.o: symtab.c
	gcc -Wall -c -o symtab.o symtab.c
narcasm.tab.h: narcasm.y
	bison -d narcasm.y
narcasm.tab.c: narcasm.tab.h
narcasm.tab.o: narasm.tab.c
	gcc -Wall -c -o narcasm.tab.o narcasm.tab.c
narcasm.yy.c: narcasm.l narcasm.tab.h
	flex -o narcasm.yy.c narcasm.l
narcasm.yy.o: narcasm.yy.c
	gcc -Wall -c -o narcasm.yy.o narcasm.yy.c
clean:
	-rm -f narcasm *.o narcasm.tab.h narcasm.tab.c narcasm.yy.c
