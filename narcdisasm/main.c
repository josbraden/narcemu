/*
@author Josh Braden <jeb071@shsu.edu>
COSC 3327 Homework 2

Main file, handles args and calls other things
*/
#include "narcdisasm.h"
#include <stdio.h>
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Please specify an input file, e.g ./narcdisasm infile.bin\n");
	}
	else if (argc > 2) {
		printf("Please limit yourself to one input file at a time.\n");
	}
	else {
		openfile(argv[1]);
	}
	return 0;
}
