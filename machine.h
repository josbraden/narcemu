/*
@author Josh Braden

Header file for the virtual machine.
*/
//Inclusions for this file
#include <stdio.h>
//Opcode definitions
#define HLT 0x0
#define LDA 0x1
#define STA 0x2
#define ADD 0x3
#define TCA 0x4
#define BRU 0x5
#define BIP 0x6
#define BIN 0x7
#define RWD 0x8
#define WWD 0x9
#define SHL 0xa
#define SHR 0xb
#define LDX 0xc
#define STX 0xd
#define TIX 0xe
#define TDX 0xf
//Structs
struct narcVM {
	//Emulator devies
	int vmstatus;
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
};
//Functions
int startMachine(int runMode, char filename[4352]);
struct narcVM initMachine(struct narcVM vm);
struct narcVM openProg(struct narcVM vm, char filename[4352]);
struct narcVM execProg(struct narcVM vm);
struct narcVM execInstr(struct narcVM vm);
unsigned short calcAddr(unsigned short mode, unsigned short address, struct narcVM vm);
unsigned short updatePSR(unsigned short acc);
