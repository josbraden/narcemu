%{
#include "narcasm.h"
%}
%%
program		: DATA variables TEXT instructs
			;
variables	: /* no variables */
			| variables variable
			;
variable	: TYPE VAL
			;
instructs	: instruct
			| instructs instruct
			;
instruct	: ZEROADDR
			| ONEADDR VAR
			| INDEX LITERAL VAR
			;
%%
