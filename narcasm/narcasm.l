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
zeroAddr	"HLT"|"SHL"|"SHR"|"RWD"
oneAddr		"LDA"|"STA"|"ADD"|"BRU"|"BIN"|"WWD"
index		"LDX"|"STX"|"TIX"|"TDX"
%%
[ \t\n]     {;} /* Consume whitespace */
comment     {;} /* Consume comments too */
".data"		{return DATA;}
".text"		{return TEXT;}
":"         {return COLON;}
var			{return VAR;}
literal		{return LITERAL;}
type		{return TYPE;}
zeroAddr	{return ZEROADDR;}
oneAddr		{return ONEADDR;}
index		{return INDEX;}
