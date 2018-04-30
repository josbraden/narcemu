# narcemu

A NARC (Not A Real Computer) Emulator by Josh Braden

NARC is a 16-bit accumulator machine, written for COSC 3347 (Computer Architecture)

The VM is of the Von Neumann variety, and has 64K (2^16) memory addresses.

Currently the machine supports the existing 16 instructions in the standard set - there are plans for an expanded set including an additional 16 instructions.

## Compilation instructions

Type 'make' to compile the emulator.

'make all' will comile the emulator and extra programs.

Run 'make clean' to delete binary files.

## Usage

narcemu accepts a filename as an argument, or omit the filename to drop to interactive mode, which also accepts relative or absolute filepaths from the console.

Example:    ./narcemu program.bin

Or:         ./narcemu /home/josh/program.bin

Or:         ./narcemu

## NARC Documentation

### Instructions/opcodes

| Instruction   | Opcode | Description |
| -----------   | ------ | ----------- |
| HLT           | 0      | Halt |
| LDA           | 1      | ACC <- M[MEM] |
| STA           | 2      | M[MEM] <- ACC |
| ADD           | 3      | ACC <- ACC + M[MEM] |
| TCA           | 4      | ACC <- !ACC + 1 (2’s Complement) |
| BRU           | 5      | Branch unconditional |
| BIP           | 6      | Branch if ACC > 0 |
| BIN           | 7      | Branch if ACC < 0 |
| RWD           | 8      | Read a word into ACC |
| WWD           | 9      | Write a word from ACC |
| SHL           | A      | Shift left ACC once |
| SHR           | B      | Shift right ACC once |
| LDX           | C      | INDEX <- M[MEM] |
| STX           | D      | M[MEM] <- INDEX |
| TIX           | E      | Test index increment: INDEX <- INDEX + 1; Branch if INDEX = 0 |
| TDX           | F      | Test Index Decrement: INDEX <- INDEX - 1; Branch if INDEX != 0 |

### Instruction Format

Each instruction in a NARC program occupies a 16-bit word. An instruction word has four fields, as shown below:

0000 1 2 33 44444444

^    ^ ^ ^  ^

|    | | |  | Address

|    | | | Index Flag

|    | | Indirect Flag

|    | Opcode Extension

| Opcode

## Future work

If I get time I'll try and get an assembler and c-ish compiler working.

A "dissasembler" is included under 'narcdisasm', which decodes and prints instructions from a binary file.  Useful for testing.
