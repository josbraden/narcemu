%option noyywrap
%{
#include <string.h>
#include <stdio.h>
#include "narcasm.tab.h"
%}
%%
[ \t\n]             {/* Consume whitespace */}
"//".*|"#".*        {/* Consume comments too */}
".data"		        {return DATA;}
".text"	    	    {return TEXT;}
":"                 {return COLON;}
"word"	            {return TYPE;}
"HLT"	            {return HLT;}
"SHL"	            {return SHL;}
"SHR"	            {return SHR;}
"RWD"	            {return RWD;}
"LDA"	            {return LDA;}
"STA"	            {return STA;}
"ADD"	            {return ADD;}
"TCA"               {return TCA;}
"BRU"	            {return BRU;}
"BIP"               {return BIP;}
"BIN"	            {return BIN;}
"WWD"	            {return WWD;}
"LDX"	            {return LDX;}
"STX"	            {return STX;}
"TIX"	            {return TIX;}
"TDX"	            {return TDX;}
[a-zA-Z]+[0-9]*     {return VAR;}
[0-9]+	            {return LITERAL;}
