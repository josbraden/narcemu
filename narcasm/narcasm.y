%{
//#include "narcasm.h"
#include "narcasm.tab.h"
#include "symtab.h"
#include <stdio.h>
#include <string.h>
struct symTab symbols;
extern char* yyin;
extern int yylex();
%}
%token DATA
%token TEXT
%token TYPE
%token VAL
%token ZEROADDR
%token ONEADDR
%token VAR
%token INDEX
%token LITERAL
%%
program		: DATA variables TEXT instructs
			;
variables	: /* no variables */
			| variables variable
			;
variable	: TYPE VAL /* install symbol */
			;
instructs	: instruct
			| instructs instruct
			;
instruct	: ZEROADDR /* write instruction binary */
			| ONEADDR VAR /* write instruction+address */
			| INDEX LITERAL VAR /* write instruction+index+value at address */
			;
%%
int main(int argc, char *argv[]) {
	//Data
	int i;
	char inFileName[4352];
	char outFileName[4352];
	FILE *ifile;
	FILE *ofile;
	//Args
	strcpy(outFileName, "a.out");
	if (argc == 1) {
        printf("Please specify an input file, or '--help' for options\n");
	}
	else {
        for (i = 1; i < argc; i++) {
            //Helptext flag
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				//print help
                printf("Usage: narcasm [options] [assembly file]\nExample:\n\tnarcasm code.asm\n\tnarcasm -o out.exe in.asm\n");
                return 0;
			}
            //Output filename flag
            else if (strcmp(argv[i], "-o") == 0) {
                i++;
                strcpy(outFileName, argv[i]);
            }
            //Else is the filename
            else {
                strcpy(inFileName, argv[i]);
            }
        }
	}
	//File handles
	//Open output file
	ofile = fopen(outFileName, "wb");
	if (ofile == NULL) {
		printf("I/O Error: output file couldn't be opened!\n");
		return 1;
	}
	//Open input file
	ifile = fopen(inFileName, "r");
	if (ifile == NULL) {
		printf("I/O Error: input file not found!\n");
		return 2;
	}
	//Set yyin to the correct file stream
	yyin = ifile;
	//Initialize symbol table and start parser
	symbols = initSymTab(symbols);
	yyparse();
	return 0;
}
