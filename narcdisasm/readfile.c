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
	infile = fopen(filename, "rb");
	if (infile == NULL) {
		printf("File does not exist!\n");
	}
	else {
		printf("Binary           Hex  Op IndirF IndexF Address\n");
		//Loop to read two bytes at a time until EOF
		while (fread(&readBuffer, 1, 2, infile) == 2) {
			byteSwap = (readBuffer >> 8) | (readBuffer << 8);
			printAll(byteSwap);
		}
	}
	fclose(infile);
}
