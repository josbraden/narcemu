/*
@author Josh Braden <jeb071@shsu.edu>
COSC 3327 Homework 2

Source file to handle the printing of the binary digits on the screen.
*/
#include "narcdisasm.h"
#include "stack.h"
#include <stdio.h>
//Calls other print functions
void printAll(unsigned short inputBuffer) {
	printA(inputBuffer);
	printB(inputBuffer);
	printC(inputBuffer);
	printD(inputBuffer);
	printE(inputBuffer);
	printF(inputBuffer);
	printf("\n");
}
//Part A: 16-bit binary number
void printA(unsigned short inputNum) {
	int i;
	char thisBit;
	//Initilize stack
	stackInit();
	//Make bits into characters, then push to stack
	//Alternatly shift and print from the left, but that's boring
	for (i = 0; i < 16; i++) {
		thisBit = ((inputNum & 1) ? '1' : '0');
		stackPush(thisBit);
		inputNum = inputNum >> 1;
	}
	//Pop characters and print them
	for (i = 0; i < 16; i++) {
		thisBit = stackPop();
		printf("%c", thisBit);
	}
	printf(" ");
}
//Part B: 4-digit hex number
void printB(unsigned short inputNum) {
    printf("%04X", inputNum);
	printf(" ");
}
//Part C: 5-bit unsigned base-10 integer extracted from bits 15-11 of the number
//Updated to print opcode and extension bit seperatly
void printC(unsigned short inputNum) {
	unsigned short exbit;
	exbit = inputNum >> 11;
	exbit = exbit & 0x1;
	inputNum = inputNum >> 12; //discard bits 0-11
	printf("%02d", inputNum);
	printf(" ");
	printf("%01d", exbit);
	printf(" ");
}
//Part D: 1-bit value extracted from bit 10 of the number
void printD(unsigned short inputNum) {
	inputNum = inputNum >> 10; //discard bits 0-9
	printf("%c", ((inputNum & 1) ? '1' : '0')); //shift and print last bit
	printf(" ");
}
//Part E: 2-bit unsigned base-10 integer extracted from bits 9-8 of the number
void printE(unsigned short inputNum) {
	inputNum = inputNum >> 8; //discard bits 0-7
	inputNum = inputNum & 0x3; //extract last two bits (8-9)
	printf("%d", inputNum);
	printf(" ");
}
//Part F: 8-bit unsigned base-10 integer extracted from bits 7-0 of the number
void printF(unsigned short inputNum) {
	inputNum = inputNum & 0xff; //Mask out all but 0-7
	printf("%03d", inputNum);
	printf(" ");
}
