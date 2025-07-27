# ChipDecode

A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) disassembler written in C. 
ChipDecode takes a .ch8 ROM as input and outputs the decoded instructions 
into a .txt file.

## Usage

Execute the program and pass the CHIP-8 ROM filename as an argument. Ex:
`./ChipDecode <ROMFILE>.ch8`. Note: The ROM file to decode must be placed 
in the same directory as the ChipDecode executable.

ChipDecode will disassemble ROM and place the resulting output in a text 
file in the program directory.

For convenience, some test ROMs are located in the [roms directory](/roms).