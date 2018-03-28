/*
@author Josh Braden

File for main virtual machine handling funtctions
*/
#include "narcemu.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>
//Function to initilize virtual machine and start either interactive or execute a filename
int startMachine(int runMode, char filename[4352]) {
    //Local data
    struct narcVM vm;
    char input[4352];
    int vmStatus;
    //initilize VM
    vm = initMachine(vm);
    vmStatus = 0;
    //Continue
    if (runMode == 0) {
        //Drop to interactive mode
        fprintf(vm.console, "No file entered, dropping to interactive mode.\n");
        strcpy(input, "");
        while (1) {
        	//Get filename from user, use "quit" and "exit" as escape patterns
        	fprintf(vm.console, ">>> ");
            fscanf(vm.input, "%s", input);
            //If help command is encountered
            if (strcmp(input, "help") == 0 || strcmp(input, "?") == 0) {
				//Print interactive mode help text
            }
            //If exit is encountered
            if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
                return vmStatus;
            }
            else {
    	        //Execute program inputted by user
    	        vmStatus = openProg(vm, input);
    	        if (vmStatus == 1) {
					fprintf(vm.console, "Input file not found!\n");
    	        }
    	        else if (vmStatus == 2) {
					fprintf(vm.console, "Out of memory\n");
    	        }
	            strcpy(input, "");
            }
        }
    }
    //Not interactive mode, execute file from the args and exit
    else {
        vmStatus = openProg(vm, filename);
        if (vmStatus == 1) {
			fprintf(vm.console, "Input file not found!\n");
        }
    }
    return vmStatus;
}
//Function to initilize a VM: set registers to 0, wipe memory, set IO device pointers
struct narcVM initMachine(struct narcVM vm) {
    int i;
    //Init registers
    vm.reg_acc = 0;
    vm.reg_memBuff = 0;
    vm.reg_instruction = 0;
    vm.reg_memAddress = 0;
    vm.reg_programCounter = 0;
    vm.reg_index1 = 0;
    vm.reg_index2 = 0;
    vm.reg_index3 = 0;
    vm.reg_processorStatus = 0;
    //Set I/O file pointers
    vm.console = stdout;
    vm.input = stdin;
    //wipe memory
    for (i = 0; i < 65536; i++) {
        vm.mem[i] = 0;
    }
    //Set extra values
    vm.pendingInstr = 0;
	return vm;
}
//Function that executes a program using the passed vm and filename
int openProg(struct narcVM vm, char filename[4352]) {
	//Local data
	FILE *infile;
	//Open file
	infile = fopen(filename, "rb");
	if (infile == NULL) {
		//Return file not found error code
		return 1;
	}
	//Load program into vm RAM and close file
	vm = loadProg(vm, infile);
	fclose(infile);
	if (vm.pendingInstr >= 65536) {
		//Return out of memory error
		return 2;
	}
	//TODO execute the program

    //Normal exit status
    return 0;
}
//Loads a program from disk into the VM's memory
//Reads a short, swaps the bytes (big endian), puts that data into vm RAM
struct narcVM loadProg(struct narcVM vm, FILE* infile) {
	int i;
	unsigned short readBuf, byteSwap;
	i = 0;
	while (fread(&readBuf, 1, 2, infile) == 2) {
		if (i >= 65536) {
			//Out of memory
			break;
		}
		byteSwap = (readBuf >> 8) | (readBuf << 8);
		vm.mem[i] = byteSwap;
		i++;
	}
	vm.pendingInstr = i;
	return vm;
}
//Executes a program stored in the VM's RAM
void execProg(struct narcVM vm) {

}
