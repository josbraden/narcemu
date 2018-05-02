%{
//#include "narcasm.h"
#include "narcasm.tab.h"
int instrKnt = 0;
int varKnt = 0;
int labelKnt = 0;
int lineKnt = 0;
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
[\n]		{lineKnt++;}
".data"		{return DATA;}
".text"		{return TEXT;}
label		{labelKnt++; return LABEL;}
var			{return VAR;}
literal		{return LITERAL;}
type		{varKnt++; return TYPE;}
zeroAddr	{instrKnt++; return ZEROADDR;}
oneAddr		{instrKnt++; return ONEADDR;}
index		{instrKnt++; return INDEX;}
%%
int totalMem() {
	return instrKnt + varKnt + labelKnt;
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
int getlineKnt() {
	return lineKnt;
}
