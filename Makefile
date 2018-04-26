narcemu: main.o machine.o
	gcc -static -o narcemu main.o machine.o
main.o: main.c narcemu.h
	gcc -Wall -c -o main.o main.c
machine.o: machine.c machine.h
	gcc -Wall -c -o machine.o machine.c
.PHONY: narcdisasm
narcdisasm:
	$(MAKE) -C narcdisasm
.PHONY: narcasm
narcasm:
	$(MAKE) -C narcasm
all:
	make narcemu
	make narcdisasm
	make narcasm
clean:
	-rm -f narcemu machine.o main.o
	cd narcdisasm/ && make clean
	cd narcasm/ && make clean
