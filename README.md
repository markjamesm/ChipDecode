# ChipDecode

A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) ROM decoder written in C. 
ChipDecode takes a .ch8 ROM as input and outputs the decoded instructions 
into a .txt file.

## Usage

Execute the program and pass the CHIP-8 ROM filename as an argument. Ex:
`./ChipDecode <ROMFILE>.ch8`. Note: The ROM file must be in the same
directory as the ChipDecode executable.

ChipDecode will then read the ROM and output a text file in the program 
directory containing the decoded instructions.

For convenience, some test ROMs are located in the ChipDecode/Roms folder.