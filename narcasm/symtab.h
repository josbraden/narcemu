/*
@author Josh Braden

Header file for symbol table
*/
//Defines
#define WORD 201
#define LABEL 202
//Struct declarations
struct symNode {
	char name[16];
	int type;
	int value;
	struct symNode *next;
};
struct symTab {
	int nodeKnt;
	struct symNode *head;
	struct symNode *tail;
};
//Functions
struct symTab initSymTab(struct symTab);
struct symTab installSym(struct symTab table);
