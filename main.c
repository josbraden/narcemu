/*
@author Josh Braden

Main file, handles args and calls functions
*/
#include "narcemu.h"
#include "machine.h"
#include <string.h>
int main(int argc, char *argv[]) {
	char *filename;
	int argStatus, runStatus;
	argStatus = argHandler(int argc, char *argv[], &filename);
	if (argStatus == 2) {
		return 0;
	}
	runStatus = startMachine(argStatus, &filename);
	if (runStatus != 0) {
		printf("VM exited with code: %d", runStatus);
	}

	return 0;
}
int argHandler(int argc, char *argv[], char **filename) {
	int i, cmpVal;
	//No args, drop to interactive mode
	if (argc == 1) {
		return 0;
	}
	else {
		for (i = 1; i <= argc; i++) {
			//Helptext flag
			if (strcmp(argv[i], "-h") == 0) {
				//print help
				filename = NULL;
				return 1;
			}
			//If not a flag, assume it's a filename
			else {
				strcpy(filename, argv[i]);
				return 2;
			}
			//TODO other args
		}
	}
}
