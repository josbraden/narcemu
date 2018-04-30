/*
@author Josh Braden

Main assembler file
*/
#include "narcasm.h"
#include "symtab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int assembler(char input[4352], char output[4352]) {
	//Local data
	int progSize;
	FILE *ofile;
	FILE *ifile;
	struct symTab table;
	unsigned short memMode;
	memMode = 0;
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
	//Set yyin to the correct file stream
	yyin = ifile;
	//init table and do first pass, determine indexing mode
	table = initSymTab(table);
	table = firstPass(table);
	progSize = totalMem();
	yyrestart(ifile);
	if (progSize > 265) {
		memMode = 4;
	}
	else {
		memMode = 0;
	}
	//Second pass
	table = secondPass(memMode, table, ofile);
	//Close files, free memory, and exit
	fclose(ifile);
	fclose(ofile);
	table = freeSymTab(table);
	return 0;
}
//First pass function: creates symbol table, as well as getting the size of the assembly program.
struct symTab firstPass(struct symTab table) {
	int token;
	char label[16];
	while (token != 0) {
		token = asmlex();
		if (token == LABEL) {
			strcpy(label, yytext);
			label[strlen((label) - 1)] = 0;
			if (lookupSym(table, label) == -1) {
				installSym(table, label, LABEL, getlineKnt());
			}
			else {
				printf("Fatal error, multiple label definitions\n");
				//todo handle errors
			}
		}
	}
	return table;
}
//Second pass function
struct symTab secondPass(unsigned short memMode, struct symTab table, FILE *ofile) {
	unsigned  short instruction;
	int token;
	char label[16];
	token = asmlex();
	//Find .data section
	while (token != DATA) {
		token = asmlex();
	}
	//Get variables until .text encountered
	while (token != TEXT) {
		strcpy(label, "");
		if (token != TYPE) {
			//error
		}
		token = asmlex();
		if (token == VAR) {
			strcpy(label, yytext);
			if (lookupSym(table, label) == -1) {
				installSym(table, label, VAR, 0);
			}
			//else already in table
		}
		else {
			//error
		}
	}
	//Process instructions
	while (token != 0) {
		instruction = 0;
		token = asmlex();
		if (token == ZEROADDR) {
			if (strcmp(yytext, "HLT") == 0) {
				instruction = 0;
			}
			else if (strcmp(yytext, "SHL") == 0) {
				instruction = 0xa;
			}
			else if (strcmp(yytext, "SHR") == 0) {
				instruction = 0xb;
			}
			else if (strcmp(yytext, "RWD") == 0) {
				instruction = 0x8;
			}
			instruction = instruction << 12;
		}
		else if (token == ONEADDR) {

		}
		else if (token == INDEX) {

		}
		else {
			//error
		}
		fprintf(ofile, "%hu", instruction);
	}
	return table;
}
