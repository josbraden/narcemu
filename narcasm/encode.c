/*
@author Josh Braden
Util function to encode an instruction to an unsigned short
*/
unsigned short encodeInstr(unsigned short opcode, unsigned short extension, unsigned short indirectFlag, unsigned short indexFlag, unsigned short address) {
	unsigned short instruction;
	instruction = 0;
	instruction = opcode << 12;
	if (extension == 1) {
		instruction = instruction & 0x800;
	}
	if (indirectFlag == 1) {
		instruction = instruction & 0x400;
	}
	if (indexFlag == 1) {
		instruction = instruction & 0x100;
	}
	else if (indexFlag == 2) {
		instruction = instruction & 0x200;
	}
	else if (indexFlag == 3) {
		instruction = instruction & 0x300;
	}
	instruction += address;
	return instruction;
}
