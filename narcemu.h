/*
@author Josh Braden

Written for COSC 3327
*/
//Structs
struct argStruct {
	char filename[4352];
	int helpFlag;
	int runMode;
};
//Function declarations
//In file main.c
struct argStruct argHandler(int argc, char *argv[], struct argStruct args);
