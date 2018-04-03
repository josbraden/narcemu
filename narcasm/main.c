/*
@author Josh Braden

Main file for assembler, handles args and calls functions
*/
#include "narcasm.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    //Local data
    int i;
    char input[4352];
    char output[4352];
    //Init
    strcpy(output, "a.out");
    //Process args
    if (argc == 1) {
        printf("Please specify an input file, or '--help' for options\n");
    }
    else {
        for (i = 1; i < argc; i++) {
            //Helptext flag
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				//print help
                printf("Usage: narcasm [options] [assembly file]\nExample:\n\tnarcasm code.asm\n\tnarcasm -o out.exe in.asm\n");
                return 0;
			}
            //Output filename flag
            else if (strcmp(argv[i], "-o") == 0) {
                i++;
                strcpy(output, argv[i]);
            }
            //Else is the filename
            else {
                strcpy(input, argv[i]);
            }
        }
        //Call assembly function
		i = assembler(input, output);
        if (i != 0) {
            printf("Error %d occurred\n", i);
        }
    }

    return 0;
}
