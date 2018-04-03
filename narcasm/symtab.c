/*
@author Josh Braden

Source file for symbol table
Currently implemented as a linear search linked list
*/
#include "symtab.h"
#include <string.h>
#include <stdlib.h>
//Initilize a symbol table by setting the knt and head node
struct symTab initSymTab(struct symTab table) {
	table.nodeKnt = 0;
	table.head = NULL;
	table.tail = NULL;
	return table;
}
//Installs a symbol
struct symTab installSym(struct symTab table, char name[16], int type, int value) {
	int lookupVal;
	//Check if symbol is already in the table
	lookupVal = lookupSym(table, name);
	if (lookupVal != -1) {
		return table;
	}
	//Allocate memory for new node
	struct symNode *newNode = (struct symNode *) malloc(sizeof(struct symNode));
	if (newNode == NULL) {
		freeSymTab(table);
		return table;
	}
	//Set node values
	strcpy(newNode->name, name);
	newNode->type = type;
	newNode->value = value;
	newNode->next = NULL;
	//If first node
	if (table.nodeKnt == 0) {
		table.head = newNode;
		table.tail = newNode;
	}
	else {
		table.tail->next = newNode;
		table.tail = newNode;
	}
	table.nodeKnt++;
	return table;
}
//Looks up a symbol in the table, returns its value
int lookupSym(struct symTab table, char name[16]) {
	struct symNode *pt;
	pt = table.head;
	while (pt != NULL) {
		if (strcmp(pt->name, name) == 0) {
			return pt->value;
		}
		pt = pt->next;
	}
	return -1;
}
//De-allocates the symbol table
struct symTab freeSymTab(struct symTab table) {
	struct symNode *pt;
	while (table.nodeKnt > 0) {
		pt = table.head;
		table.head = table.head->next;
		free(pt);
		table.nodeKnt--;
	}
	return table;
}
