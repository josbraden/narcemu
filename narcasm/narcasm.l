%option noyywrap
%{
#include <string.h>
#include <stdio.h>
#include "narcasm.tab.h"
%}
comment     "//"*|"#"*
var			[a-zA-Z]+[0-9]*
literal		[0-9]+
type		"word"
%%
[ \t\n]     {;} /* Consume whitespace */
comment     {;} /* Consume comments too */
".data"		{return DATA;}
".text"		{return TEXT;}
":"         {return COLON;}
var			{return VAR;}
literal		{return LITERAL;}
type		{return TYPE;}
"HLT"		{return HLT;}
"SHL"		{return SHL;}
"SHR"		{return SHR;}
"RWD"		{return RWD;}
"LDA"		{return LDA;}
"STA"		{return STA;}
"ADD"		{return ADD;}
"BRU"		{return BRU;}
"BIN"		{return BIN;}
"WWD"		{return WWD;}
"LDX"		{return LDX;}
"STX"		{return STX;}
"TIX"		{return TIX;}
"TDX"		{return TDX;}
