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
unsigned short indexFlag;
unsigned short instruction;
FILE* ifile;
FILE* ofile;
%}
%token DATA
%token TEXT
%token LABEL
%token COLON
%token LITERAL
%token TYPE
%token VAL
%token VAR
%token HLT
%token SHL
%token SHR
%token RWD
%token LDA
%token STA
%token ADD
%token BRU
%token BIN
%token WWD
%token LDX
%token STX
%token TIX
%token TDX
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
instruct	: zeroaddr
			| oneaddr
			| index
			| label
			;
zeroaddr	: HLT {mem++; putc(0x0, ofile);}
			| SHL {mem++; putc(0xa, ofile);}
			| SHR {mem++; putc(0xb, ofile);}
			| RWD {mem++; putc(0x8, ofile);}
			| WWD {mem++; putc(0x9, ofile);}
			;
oneaddr		: LDA operand {mem++; /* placeholder */}
			| STA VAR {mem++; /* placeholder */}
			| ADD operand {mem++; /* placeholder */}
			| BRU operand {mem++; /* placeholder */}
			| BIN operand {mem++; /* placeholder */}
			;
index		: LDX {mem++; /* placeholder */}
			| STX {mem++; /* placeholder */}
			| TIX {mem++; /* placeholder */}
			| TDX {mem++; /* placeholder */}
			;
label		: VAR {strcpy(buff, yytext);} COLON {installSym(symbols, buff, LABEL, mem);}
			;
operand		: VAR
			| LITERAL
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
	fclose(ifile);
	fclose(ofile);
	return 0;
}
void yyerror(const char* err) {
	printf("Error placeholder\n");
}
