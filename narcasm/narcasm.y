%{
//Inclusions
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Lex stuff
extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
//Functions for this file
void yyerror(const char* err);
//Data
struct symTab symbols;
char buff[16];
int mem;
FILE* ifile;
FILE* ofile;
%}
%token DATA
%token TEXT
%token LABEL
%token COLON
%token TYPE
%token VAL
%token VAR
%token ZEROADDR
%token ONEADDR
%token INDEX
%token LITERAL
%start program
%%
program		: DATA variables TEXT instructs
			;
variables	: /* no variables */
			| variables variable
			;
variable	: TYPE VAR {mem++; installSym(symbols, yytext, VAR, 0);}
			;
instructs	: instruct
			| instructs instruct
			;
instruct	: ZEROADDR {
							mem++;
							if (strcmp(yytext, "HLT") == 0) {
								putc(0x0, ofile);
							}
							else if (strcmp(yytext, "SHL") == 0) {
								putc(0xa, ofile);
							}
							else if (strcmp(yytext, "SHR") == 0) {
								putc(0xb, ofile);
							}
							else if (strcmp(yytext, "RWD") == 0) {
								putc(0x8, ofile);
							}
						}
			| ONEADDR VAR {
							mem++;

						}
			| INDEX LITERAL VAR {
							mem++;

						}
			| label
			;
label		: VAR {strcpy(buff, yytext);} COLON {installSym(symbols, buff, LABEL, mem);}
			;
%%
int main(int argc, char *argv[]) {
	//Local data
	int i;
	char input[4352];
    char output[4352];
	//Init
	mem = 0;
	symbols = initSymTab(symbols);
	strcpy(buff, "");
	strcpy(output, "a.out");
	//Handle args
	if (argc == 1) {
        printf("Please specify an input file, or '--help' for options\n");
		//If no input, exit
		symbols = freeSymTab(symbols);
		return 0;
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
                strcpy(output, argv[i]);
            }
            //Else is the filename
            else {
                strcpy(input, argv[i]);
            }
        }
	}
	//Open files
	ifile = fopen(input, "r");
	if (ifile == NULL) {
		printf("I/O Error: input file not found!\n");
		symbols = freeSymTab(symbols);
		return 0;
	}
	ofile = fopen(output, "wb");
	if (ofile == NULL) {
		printf("I/O Error: output file couldn't be opened!\n");
		symbols = freeSymTab(symbols);
		return 0;
	}
	yyin = ifile;
	//Start parsing
	yyparse();
	//Free mem and exit
	symbols = freeSymTab(symbols);
	return 0;
}
void yyerror(const char* err) {
	printf("Error placeholder\n");
}
