/*
@author Josh Braden

File for main virtual machine handling funtctions
Note on opcode extension bit:
Currently no instructions are associated with opcodes 0x10..0x1f, so they act as NOOPS
In the event of instruction extension, more case statements need to be added to execInstr()
*/
#include "narcemu.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>
//Start vm in interactive, or execute a filename
int startMachine(int runMode, char filename[4352]) {
    //Local data
    struct narcVM vm;
    char input[4352];
    //initilize VM
    vm = initMachine(vm);
    //Continue
    if (runMode == 0) {
        //Drop to interactive mode
        fprintf(vm.console, "No file entered, dropping to interactive mode.\nType 'help' for options.\n");
        while (1) {
	        strcpy(input, "");
        	fprintf(vm.console, ">>> ");
            fscanf(vm.input, "%s", input);
            //If help command is encountered
            if (strcmp(input, "help") == 0 || strcmp(input, "?") == 0) {
                fprintf(vm.console, "Enter a relative or absolute filename to execute.\nType 'help' or '?' for this text.\nType 'quit' or 'exit' to terminate.\n");
            }
            //If exit is encountered
            else if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) {
                return vm.vmstatus;
            }
            else {
    	        //Execute program inputted by user
    	        vm = openProg(vm, input);
    	        if (vm.vmstatus == 1) {
					fprintf(vm.console, "Input file not found!\n");
    	        }
    	        else if (vm.vmstatus == 2) {
					fprintf(vm.console, "Out of memory\n");
    	        }
	            strcpy(input, "");
            }
        }
    }
    //Not interactive mode, execute file from the args and exit
    else {
        vm = openProg(vm, filename);
        if (vm.vmstatus == 1) {
			fprintf(vm.console, "Input file not found!\n");
        }
    }
    return vm.vmstatus;
}
//Initilizes a VM: set registers to 0, wipe memory, set IO device pointers
struct narcVM initMachine(struct narcVM vm) {
    int i;
    //Init emulator devices
    vm.vmstatus = 0;
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
	return vm;
}
//Function that executes a program using the passed vm and filename
struct narcVM openProg(struct narcVM vm, char filename[4352]) {
	//Local data
	FILE *infile;
	int i;
	unsigned short readBuf, byteSwap;
	//Open file
	infile = fopen(filename, "rb");
	if (infile == NULL) {
		//Return with file not found error code
		vm.vmstatus = 1;
		return vm;
	}
	//Load program into vm RAM and close input file
	i = 0;
	while (fread(&readBuf, 1, 2, infile) == 2) {
		if (i >= 65536) {
			//VM out of memory, error
            fclose(infile);
            vm.vmstatus = 2;
			return vm;
		}
		byteSwap = (readBuf >> 8) | (readBuf << 8);
		vm.mem[i] = byteSwap;
		i++;
	}
	fclose(infile);
    //Call execute function
    vm = execProg(vm);
	return vm;
}
//Executes a program stored in the VM's RAM
struct narcVM execProg(struct narcVM vm) {
    //Init: first instruction at address 0
    vm.reg_programCounter = 0;
    //Program execution loop
    while (1) {
        /***************Fetch***************/
        vm.reg_instruction = vm.mem[vm.reg_programCounter];
        vm.reg_programCounter++;
        //Decode and execute instruction
        vm = execInstr(vm);
        //Exit if told to halt
        if (vm.vmstatus == 0) {
            fprintf(vm.console, "Execution completed.\n");
            return vm;
        }
        //Exit if illegal instruction
        else if (vm.vmstatus < 0 || vm.vmstatus > 0x1f) {
            return vm;
        }
    }
}
//Decodes and executes the instruction in the instruction register
struct narcVM execInstr(struct narcVM vm) {
    unsigned short opcode, address, mode;
    opcode = 0;
    /***************Decode***************/
    //Get extension bit
    opcode = vm.reg_instruction >> 11;
    opcode = opcode & 0x1;
    if (opcode == 1) { //if extension bit set, set opcode to 0xf+1
        opcode = 0x10;
    }
    //Get opcode
    opcode += vm.reg_instruction >> 12;
    //Get address and mode
    address = vm.reg_instruction & 0xff;
    mode = vm.reg_instruction >> 8;
    mode = mode & 0x7;
    //Calculate effective address
    vm.reg_memAddress = calcAddr(mode, address, vm);
    /***************Execute***************/
    //Opcode decision case
    switch (opcode) {
        case HLT:
            break;
        case LDA:
            vm.reg_acc = vm.mem[vm.reg_memAddress];
            break;
        case STA:
            vm.mem[vm.reg_memAddress] = vm.reg_acc;
            break;
        case ADD:
            vm.reg_acc += vm.mem[vm.reg_memAddress];
            break;
        case TCA:
            vm.reg_acc = ~vm.reg_acc;
            vm.reg_acc++;
            break;
        case BRU:
            vm.reg_programCounter = vm.mem[vm.reg_memAddress];
            break;
        case BIP:
            if (((vm.reg_processorStatus >> 2) & 3) == 0) {
                vm.reg_programCounter = vm.mem[vm.reg_memAddress];
            }
            break;
        case BIN:
            if (((vm.reg_processorStatus >> 3) & 1) == 1) {
                vm.reg_programCounter = vm.mem[vm.reg_memAddress];
            }
            break;
        case RWD:
            fprintf(vm.console, "> ");
            fscanf(vm.input, "%hu", &vm.reg_acc);
            fprintf(vm.console, "Testing, ACC: %hu\n", vm.reg_acc);
            break;
        case WWD:
            fprintf(vm.console, "%hu\n", vm.reg_acc);
            break;
        case SHL:
            vm.reg_acc = vm.reg_acc << 1;
            break;
        case SHR:
            vm.reg_acc = vm.reg_acc >> 1;
            break;
        //Index register instructions: need to resolve indirection if any and use mode as register selection
        case LDX:
            if (mode >=4 && mode <= 7) {
                address = vm.mem[address];
            }
            switch (mode) {
                case 1:
                    vm.reg_index1 = vm.mem[address];
                    break;
                case 2:
                    vm.reg_index2 = vm.mem[address];
                    break;
                case 3:
                    vm.reg_index3 = vm.mem[address];
                    break;
                default:
                    fprintf(vm.console, "Illegal instruction encountered\n");
                    vm.vmstatus = mode;
                    return vm;
            }
            break;
        case STX:
            if (mode >=4 && mode <= 7) {
                address = vm.mem[address];
            }
            switch (mode) {
                case 1:
                    vm.mem[address] = vm.reg_index1;
                    break;
                case 2:
                    vm.mem[address] = vm.reg_index2;
                    break;
                case 3:
                    vm.mem[address] = vm.reg_index3;
                    break;
                default:
                    vm.vmstatus = mode;
                    return vm;
            }
            break;
        case TIX:
            if (mode >=4 && mode <= 7) {
                address = vm.mem[address];
            }
            switch (mode) {
                case 1:
                    vm.reg_index1++;
                    if (vm.reg_index1 == 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
                case 2:
                    vm.reg_index2++;
                    if (vm.reg_index2 == 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
                case 3:
                    vm.reg_index3++;
                    if (vm.reg_index3 == 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
            }
            break;
        case TDX:
            if (mode >=4 && mode <= 7) {
                address = vm.mem[address];
            }
            switch (mode) {
                case 1:
                    vm.reg_index1--;
                    if (vm.reg_index1 != 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
                case 2:
                    vm.reg_index2--;
                    if (vm.reg_index2 != 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
                case 3:
                    vm.reg_index3--;
                    if (vm.reg_index3 != 0) {
                        vm.reg_programCounter = vm.mem[address];
                    }
                    break;
            }
            break;
        default:
            break;
    }
    vm.vmstatus = opcode;
    return vm;
}
//Function to calculate the effective address from a memory mode (instruction bits 8-10) and an address (instruction bits 0-7)
unsigned short calcAddr(unsigned short mode, unsigned short address, struct narcVM vm) {
    switch (mode) {
        //Direct addressing
        case 0:
            return address;
        //Index addressing
        case 1:
            return address + vm.reg_index1;
        case 2:
            return address + vm.reg_index2;
        case 3:
            return address + vm.reg_index3;
        //Indirect addressing
        case 4:
            return vm.mem[address];
        //Indirect indexed addressing
        case 5:
            return vm.mem[(address + vm.reg_index1)];
        case 6:
            return vm.mem[(address + vm.reg_index2)];
        case 7:
            return vm.mem[(address + vm.reg_index3)];
        default:
            return address;
    }
}
