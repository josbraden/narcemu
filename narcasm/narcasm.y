%{
#include "narcasm.h"
#include "symtab.h"
struct symTab table;
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
