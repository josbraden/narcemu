/*
@author Josh Braden

Header file for symbol table
*/
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
struct symTab initSymTab(struct symTab table);
struct symTab installSym(struct symTab table, char name[16], int type, int value);
struct symTab freeSymTab(struct symTab table);
int lookupSym(struct symTab table, char name[16]);
