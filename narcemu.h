/*
@author Josh Braden

Written for COSC 3327
Header file for narcemu
*/
//Structs
struct argStruct {
	char filename[4352];
	int helpFlag;
	int runMode;
};
//Function declarations
struct argStruct argHandler(int argc, char *argv[], struct argStruct args);
