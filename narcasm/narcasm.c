/*
@author Josh Braden

Main assembler file
*/
#include "narcasm.h"
#include <stdio.h>
int assembler(char input[4352], char output[4352]) {
	//Local data
	FILE *ofile;
	FILE *ifile;
	//Open output file
	ofile = fopen(output, "wb");
	if (ofile == NULL) {
		printf("I/O Error: output file couldn't be opened!\n");
		return 1;
	}
	//Open input file
	ifile = fopen(input, "r");
	if (ifile == NULL) {
		printf("I/O Error: input file not found!\n");
		return 2;
	}

	return 0;
}
