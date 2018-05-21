%{
//Inclusions
#include "symtab.h"
#include "encode.h"
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
unsigned short instruction, address, indexFlag;
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
%token TCA
%token BRU
%token BIN
%token WWD
%token LDX
%token STX
%token TIX
%token TDX
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
zeroaddr	: HLT {mem++; instruction = encodeInstr(0x0, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| TCA {mem++; instruction = encodeInstr(0x4, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| SHL {mem++; instruction = encodeInstr(0xa, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| SHR {mem++; instruction = encodeInstr(0xb, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| RWD {mem++; instruction = encodeInstr(0x8, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| WWD {mem++; instruction = encodeInstr(0x9, 0, 0, 0, 0); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			;
oneaddr		: LDA operand {mem++; instruction = encodeInstr(0x1, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| STA operand {mem++; instruction = encodeInstr(0x2, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| ADD operand {mem++; instruction = encodeInstr(0x3, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| BRU operand {mem++; instruction = encodeInstr(0x5, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| BIN operand {mem++; instruction = encodeInstr(0x7, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			;
index		: LDX LITERAL {indexFlag = atoi(yytext);} operand {mem++; instruction = encodeInstr(0xc, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| STX LITERAL {indexFlag = atoi(yytext);} operand {mem++; instruction = encodeInstr(0xd, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| TIX LITERAL {indexFlag = atoi(yytext);} operand {mem++; instruction = encodeInstr(0xe, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			| TDX LITERAL {indexFlag = atoi(yytext);} operand {mem++; instruction = encodeInstr(0xf, 0, 0, 0, address); fwrite(&instruction, 1, sizeof(unsigned short), ofile);}
			;
label		: VAR {strcpy(buff, yytext);} COLON {installSym(symbols, buff, LABEL, mem);}
			;
operand		: VAR {if (lookupSym(symbols, yytext) == -1) {yyerror(yytext);} else {address = lookupSym(symbols, yytext);}}
			| LITERAL {address = atoi(yytext);}
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
