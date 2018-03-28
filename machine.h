/*
@author Josh Braden

Header file for the virtual machine.
*/
//Inclusions for this file
#include <stdio.h>
//Structs
struct narcVM {
	//IO devices
    FILE* console;
    FILE* input;
    //Memory
    unsigned short mem[65536];
    //Registers
    unsigned short reg_acc;
    unsigned short reg_memBuff;
    unsigned short reg_instruction;
    unsigned short reg_memAddress;
    unsigned short reg_programCounter;
    unsigned short reg_index1;
    unsigned short reg_index2;
    unsigned short reg_index3;
    unsigned short reg_processorStatus;
    //Extra values
    int pendingInstr;
};
//Functions
int startMachine(int runMode, char filename[4352]);
struct narcVM initMachine(struct narcVM vm);
int openProg(struct narcVM vm, char filename[4352]);
struct narcVM loadProg(struct narcVM vm, FILE* infile);
int execProg(struct narcVM vm);
