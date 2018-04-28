# narcemu

A NARC (Not A Real Computer) Emulator by Josh Braden

NARC is a 16-bit accumulator machine, written for COSC 3347 (Computer Architecture)

The VM is of the Von Neumann variety, and has 64K (2^16) memory addresses.

Currently the machine supports the existing 16 instructions in the standard set - there are plans for an expanded set including an additional 16 instructions.

## Compilation instructions

Type 'make' to compile.

Type 'make clean' to delete binary files.

## Usage

narcemu accepts a filename as an argument, or omit the filename to drop to interactive mode, which also accepts relative or absolute filepaths from the console.

Example:    ./narcemu program.bin

Or:         ./narcemu /home/josh/program.bin

Or:         ./narcemu

## Instructions/opcodes

| Instruction   | Opcode |
| -----------   | ------ |
| HLT           | 0      |
| LDA           | 1      |
| STA           | 2      |
| ADD           | 3      |
| TCA           | 4      |
| BRU           | 5      |
| BIP           | 6      |
| BIN           | 7      |
| RWD           | 8      |
| WWD           | 9      |
| SHL           | A      |
| SHR           | B      |
| LDX           | C      |
| STX           | D      |
| TIX           | E      |
| TDX           | F      |

## Future work

If I get time I'll try and get an assembler and c-ish compiler working.
