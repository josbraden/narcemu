/*
@author Josh Braden
Header file for the virtual machine.
*/
//Inclusions for this file
#include <stdio.h>
//Structs
struct narcVM {
    FILE* console;
    unsigned short mem[65536];
    unsigned short reg_acc;
    unsigned short reg_memBuff;
    unsigned short reg_instruction;
    unsigned short reg_memAddress;
    unsigned short reg_programCounter;
    unsigned short reg_index1;
    unsigned short reg_index2;
    unsigned short reg_index3;
    unsigned short reg_processorStatus;
};
//Functions
int startMachine(struct argStruct args);
struct narcVM initMachine(struct narcVM vm);
int openProg(struct narcVM vm, char filename[4352], int memMode);
