/*
@author Josh Braden

*/
#include "narcemu.h"
#include <string.h>
int main(int argc, char *argv[]) {

	return 0;
}
char* argHandler(int argc, char *argv[]) {
	int i, cmpVal;
	//No args, drop to interactive mode
	if (argc == 1) {
		//No filename
	}
	else {
		for (i = 1; i <= argc; i++) {
			//Helptext flag
			if (strcmp(argv[i], "-h") == 0) {
				//print help
			}
			//If not a flag, assume it's a filename
			else {
				//TODO insert filename to list
			}
			//TODO other options
		}
	}
}
