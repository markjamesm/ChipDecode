# ChipDecode

A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) disassembler written in C. 
ChipDecode takes a .ch8 ROM as input and outputs the decoded instructions 
into a text file.

## Usage

Place your ROM file in the same directory as the ChipDecode executable and execute ChipDecode 
with the ROM file as an argument. Ex: `./ChipDecode <ROMNAME>.ch8`. 

ChipDecode will disassemble the ROM and place the output in a text file in the program 
directory in the format `<ROMNAME>.txt`. The decoded instructions are in the following format:

```text
<Opcode>: Instruction description
```
Example output:
```text

00E0: Clear the screen
A: Set I to 0x2A
6: Set v[0x0] to 0xC
6: Set v[0x1] to 0x8
D: Draw (8 * 0xF) pixel sprite at position v[0x0], v[0x1] with data starting at the address in I
7: Add 0x9 to v[0x0]
```

## Test ROMs

For convenience, some test ROMs are located in the [roms directory](/roms).