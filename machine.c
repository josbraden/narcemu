/*
@author Josh Braden

File for main virtual machine handling funtctions
*/
#include "narcemu.h"
#include "machine.h"
#include <stdio.h>
//Function to initilize virtual machine and start either interactive or execute a filename
int startMachine(int argStatus, **filename) {
    //Local data
    struct narcVM vm;
    char input[256];
    int vmStatus;
    //initilize VM
    vm = initMachine(vm);
    vmStatus = 0;
    //Continue
    if (argStatus == 0) {
        //Drop to interactive mode
        strcpy(input, "");
        while(true) {
            fscanf(stdin, "%s", input);
            if (strcmp(input, "quit") != 0 && strcmp(input, "exit") != 0) {
                return vmStatus;
            }
            vmStatus = execProg(vm, input);
            strcpy(input, "");
        }
    }
    else {
        vmStatus = execProg(vm, filename);
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
        vm.mem = 0;
    }
}
//Function that executes a program using the passed vm and filename
int execProg(struct narcVM vm, char* filename) {

    //Normal status
    return 0;
}
