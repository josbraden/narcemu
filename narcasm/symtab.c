/*
@author Josh Braden

Source file for symbol table
Currently implemented as a linear search linked list
*/
#include "symtab.h"
#include <string.h>
//Initilize a symbol table by setting the knt and head node
struct symTab initSymTab(struct symTab table) {
	table.nodeKnt = 0;
	table.head = NULL;
	table.tail = NULL;
	return table;
}
//Installs a symbol
struct symTab installSym(struct symTab table, char name[16], int type, int value) {
	//Allocate memory for new node
	struct symNode *newNode = malloc(sizeof(struct symNode));
	if (newNode == NULL) {
		//Free entire table and quit
	}
	//Set node values
	strcpy(newNode.name, name);
	newNode.type = type;
	newNode.value = value;
	newNode.next = NULL;
	//If first node
	if (table.nodeKnt == 0) {
		table.head = &newNode;
		table.tail = &newNode;
		table.nodeKnt++;
	}
}
