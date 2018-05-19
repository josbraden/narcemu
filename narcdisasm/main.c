/*
@author Josh Braden <jeb071@shsu.edu>
COSC 3327 Homework 2

Main file, handles args and calls other things
*/
#include "narcdisasm.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
	char filename[4352];
	int i, mode;
	mode = ASSEMBLY;
	if (argc == 1) {
		printf("Please specify an input file, e.g ./narcdisasm infile.bin, or use -h for help\n");
	}
	else {
		for (i = 1; i < argc; i++) {
			//Helptext flag
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				//print help
			}
			//Print old-style breakdown instead of instructions
			else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--breakdown") == 0) {
				mode = BREAKDOWN;
			}
			//Doesn't match anything else; is a filename
			else {
				strcpy(filename, argv[i]);
			}
		}
		//TODO: change this to pass mode
		openfile(filename);
	}
	return 0;
}
