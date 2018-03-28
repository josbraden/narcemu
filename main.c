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
	//If help called, don't continue
	if (args.helpFlag == 1) {
		return 0;
	}
	//Start machine
	runStatus = startMachine(args.runMode, args.filename);
	if (runStatus != 0) {
		printf("VM exited with code: %d", runStatus);
	}

	return 0;
}
struct argStruct argHandler(int argc, char *argv[], struct argStruct args) {
	int i;
	//No args, drop to interactive mode
	if (argc == 1) {
		args.runMode = 0;
	}
	else {
		for (i = 1; i <= argc; i++) {
			//Helptext flag
			if (strcmp(argv[i], "-h") == 0) {
				//print help
				args.helpFlag = 1;
				return args;
			}
			//TODO other args
			//If not a flag, assume it's a filename
			else {
				strcpy(args.filename, argv[i]);
				args.runMode = 1;
			}
		}
	}
	return args;
}
