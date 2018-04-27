/*
@author Josh Braden <jeb071@shsu.edu>
COSC 3327 Homework 2

Source code file to handle file read operations.
Does file opening/closing (and associated error handling)
and the actual reading of the binary
*/
#include "narcdisasm.h"
#include <stdio.h>
//Function to open the file and read in loop
void openfile(char *filename) {
	FILE *infile;
	unsigned short readBuffer, byteSwap;
	int instrKnt;
	instrKnt = 0;
	infile = fopen(filename, "rb");
	if (infile == NULL) {
		printf("Input file not found\n");
	}
	else {
		printf("          Binary           Hex  Op E IndirF IndexF Address\n");
		//Loop to read two bytes at a time until EOF
		while (fread(&readBuffer, 1, 2, infile) == 2) {
			byteSwap = (readBuffer >> 8) | (readBuffer << 8);
			printf("%8d: ", instrKnt);
			instrKnt++;
			printAll(byteSwap);
		}
	}
	fclose(infile);
}
