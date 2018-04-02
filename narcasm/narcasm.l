%{
#include "narcasm.h"
int instrKnt = 0;
%}
comment     "//"*
%%
[ \t]       /* Consume whitespace */
comment     /* Consume comments too */