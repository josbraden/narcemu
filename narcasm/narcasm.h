/*
@author Josh Braden

Assembler header file
*/
//Flex defines
//Rename yylex() function to something unique to assembler
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
//**********Function prototypes**********
//Lexical analyser
int asmlex();
int totalMem();
int getvarKnt();
int getinstrKnt();
int getlabelKnt();
//In narcasm.c
int assembler(char input[4352], char output[4352]);
