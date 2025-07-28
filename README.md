# ChipDecode

A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) disassembler written in C. 

## Usage

`./ChipDecode <file>.ch8`

ChipDecode will place the output in a text file inside the program directory as 
`<file>.txt`. The decoded instructions are in the
[Octo Assembly Language](https://johnearnest.github.io/Octo/docs/Manual.html#octo-assembly-language)
format.

## Test ROMs

For convenience, some test ROMs are located in the [roms directory](/roms). You can test a disassembled
file by loading it into the [Octo Web VM](https://johnearnest.github.io/Octo/) and running it.