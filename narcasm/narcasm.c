/*
@author Josh Braden

Main assembler file
*/
#include "narcasm.h"
#include "symtab.h"
#include <stdio.h>
#include <string.h>
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
	//Close files and exit
	fclose(ifile);
	fclose(ofile);
	return 0;
}
//First pass function: creates symbol table, as well as getting the size of the assembly program.
struct symTab firstPass(struct symTab table) {
	int token;
	char label[16];
	while (token != EOF) {
		token = asmlex();
		if (token == LABEL) {
			strcpy(label, yytext);
			label[strlen((label) - 1)] = 0;
			if (lookupSym(table, label) == -1) {
				installSym(table, label, LABEL, getlineKnt());
			}
			else {
				//Fatal error, multiple label definitions
			}
		}
	}
	return table;
}
//Second pass function
struct symTab secondPass(unsigned short memMode, struct symTab table, FILE *ofile) {

	return table;
}