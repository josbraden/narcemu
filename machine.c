/*
@author Josh Braden

File for main virtual machine handling funtctions
*/
#include "narcemu.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>
//Function to initilize virtual machine and start either interactive or execute a filename
int startMachine(struct argStruct args) {
    //Local data
    struct narcVM vm;
    char input[4352];
    int vmStatus;
    //initilize VM
    vm = initMachine(vm);
    vmStatus = 0;
    //Continue
    if (args.runMode == 0) {
        //Drop to interactive mode
        fprintf(vm.console, "No file entered, dropping to interactive mode.\n");
        strcpy(input, "");
        while (1) {
        	//Get filename from user, use "quit" and "exit" as escape patterns
        	fprintf(vm.console, ">>> ");
            fscanf(stdin, "%s", input);
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
    	        vmStatus = openProg(vm, input, args.memMode);
    	        if (vmStatus == 1) {
					fprintf(console, "Input file not found!\n");
    	        }
	            strcpy(input, "");
            }
        }
    }
    //Not interactive mode, execute file from the args and exit
    else {
        vmStatus = openProg(vm, args.filename, args.memMode);
        if (vmStatus == 1) {
			fprintf(console, "Input file not found!\n");
        }
    }
    return vmStatus;
}
//Function to initilize a VM: set registers to 0, wipe memory, set console file
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
    //Set console file pointer
    vm.console = stdout;
    //wipe memory
    for (i = 0; i < 65536; i++) {
        vm.mem[i] = 0;
    }
	return vm;
}
//Function that executes a program using the passed vm and filename
int openProg(struct narcVM vm, char filename[4352], int memMode) {
	//Local data
	FILE *infile;
	//Open file
	infile = fopen(filename, "rb");
	if (infile == NULL) {
		//Return file not found error code
		return 1;
	}
	//If we're running in static mode, need to load program into memory before execution
	if (memMode == 1) {

	}
	//else run directly off disk
	else {

	}
    //Normal exit status
    return 0;
}
//Executes a program from memory
