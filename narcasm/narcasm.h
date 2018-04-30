/* @author Josh Braden

Assembler header file
*/
//Inclusions for this file
#include <stdio.h>
//Flex defines
#define yylex asmlex
//Token Definitions
#define DATA 101
#define TEXT 102
#define LABEL 103
#define VAR 104
#define LITERAL 105
#define TYPE 106
#define ZEROADDR 107
#define ONEADDR 108
#define INDEX 109
#define WORD 110
//Other flex preprocessing
extern FILE *yyin;
extern char *yytext;
extern void yyrestart(FILE *input_file);
//Bison defines
#define yyparse asmparse
//**********Function prototypes**********
//Lexical analyser
int asmlex();
int totalMem();
int getvarKnt();
int getinstrKnt();
int getlabelKnt();
int getlineKnt();
//In narcasm.c
int assembler(char input[4352], char output[4352]);
struct symTab firstPass(struct symTab table);
struct symTab secondPass(unsigned short memMode, struct symTab table, FILE *ofile);
