/* @author Josh Braden

Assembler header file
*/
//Inclusions for this file
//#include <stdio.h>
//Flex defines
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
//extern FILE *yyin;
//extern char *yytext;
//extern void yyrestart(FILE *input_file);
//Bison defines
//**********Function prototypes**********
//Lexical analyser
int totalMem();
int getvarKnt();
int getinstrKnt();
int getlabelKnt();
int getlineKnt();
