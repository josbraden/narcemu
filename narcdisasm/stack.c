/*
@author Josh Braden <jeb071@shsu.edu>
COSC 3327 Homework 2

Simple char stack, works as a string inverter for outputs
Only 16 bytes are needed, because the most data that gets pushed is one 16 bit number.
*/
#include "stack.h"
#define STACKSIZE 16
//Shared data: stack space and knt
char stackSpace[STACKSIZE];
int stackKnt;
//Function to init stack to empty
void stackInit() {
	stackKnt = 0;
}
void stackPush(char input) {
	//Not full
	if (stackKnt <= STACKSIZE) {
		stackSpace[stackKnt] = input;
		stackKnt++;
	} //else handle overflow error
}
char stackPop() {
	char output;
	stackKnt--;
	//Empty
	if (stackKnt < 0) {
		stackKnt = 0;
		return 'z';
	}
	//Not empty
	else {
		output = stackSpace[stackKnt];
		return output;
	}
}
