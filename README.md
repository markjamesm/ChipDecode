# ChipDecode

A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) disassembler written in C. 

## Usage

`./ChipDecode <file>.ch8`

ChipDecode will place the output in a text file inside the program directory as 
`<file>.txt`. The decoded instructions are in the following format:

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