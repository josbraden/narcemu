/*
@author Josh Braden

Main file, handles args and calls functions
*/
#include "narcemu.h"
#include "machine.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
	//Local data
	struct argStruct args;
	int runStatus;
	args = argHandler(argc, argv, args);
	if (args.helpFlag == 1) {
		return 0;
	}
	//Start machine
	runStatus = startMachine(args.runMode, args.filename);
	if (runStatus != 0) {
		printf("VM exited with code: %d\n", runStatus);
	}
	return 0;
}
//Args are currently helptext or program file name
struct argStruct argHandler(int argc, char *argv[], struct argStruct args) {
	int i;
	if (argc == 1) {
		args.runMode = 0;
		return args;
	}
	//Else process arguments
	else {
		for (i = 1; i < argc; i++) {
			//Helptext flag
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				//print help
				printf("Usage: narcemu [options]|[program name]\nExample: ./narcemu program.bin\n");
				args.helpFlag = 1;
				return args;
			}
			//If not a flag, use it as a filename
			else {
				strcpy(args.filename, argv[i]);
				args.runMode = 1;
				return args;
			}
		}
	}
	return args;
}
