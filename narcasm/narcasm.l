%{
#include "narcasm.h"
int instrKnt = 0;
int varKnt = 0;
int labelKnt = 0;
%}
comment     "//".*|"#".*
label		[a-zA-Z]+[0-9]*":"
var			[a-zA-Z]+[0-9]*
literal		[0-9]+
type		"word"
zeroAddr	"HLT"|"SHL"|"SHR"|"RWD"
oneAddr		"LDA"|"STA"|"ADD"|"BRU"|"BIN"|"WWD"
index		"LDX"|"STX"|"TIX"|"TDX"
%%
[ \t]       /* Consume whitespace */
comment     /* Consume comments too */
".data"		{ return DATA; }
".text"		{ return TEXT; }
label		{ labelKnt++; return LABEL; }
var			{ return VAR; }
literal		{ return LITERAL; }
type		{ varKnt++; return TYPE; }
zeroAddr	{ instrKnt++; return ZEROADDR; }
oneAddr		{ instrKnt++; return ONEADDR; }
index		{ instrKnt++; return INDEX; }
%%
int totalMem() {
	return instrKnt + varKnt;
}
int getvarKnt() {
	return varKnt;
}
int getinstrKnt() {
	return instrKnt;
}
int getlabelKnt() {
	return labelKnt;
}
