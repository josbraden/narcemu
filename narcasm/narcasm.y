%{
#include "symtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* err);
%}
%token DATA
%token TEXT
%token TYPE
%token LABEL
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
int main() {

	return 0;
}
void yyerror(const char* err) {

}
