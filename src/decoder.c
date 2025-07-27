#include <stdio.h>
#include <stdlib.h>

#include "../include/decoder.h"

void decode_0000(const unsigned short instruction) {
    switch (instruction & 0x0FFF) {
        case 0x00E0:
            printf("0x%04X: Clear the screen\n", instruction);
            break;
        case 0x00EE:
            printf("0x%04X: Return from subroutine to address pulled from stack\n", instruction);
            break;
        default:
            break;
    }
}

void decode(const unsigned char *instruction_bytes) {
    if (!instruction_bytes) {
        fputs("Error reading instruction\n",stderr);
        exit(EXIT_FAILURE);
    }

    const unsigned short instruction = (unsigned) instruction_bytes[0] << 8 | instruction_bytes[1];
    // printf("Decoded instruction %04X\n",instruction & 0xF000);
    const unsigned char x = (instruction & 0x0F00) >> 8;
    //const unsigned char y = (instruction & 0x00F0) >> 4;
    //const unsigned char n = instruction & 0x000F;
    const unsigned char nn = instruction & 0x00FF;
    //const unsigned char nnn = instruction & 0x0FFF;

    switch (instruction & 0xF000) {
        case 0x0000:
            decode_0000(instruction);
            break;
        case 0x6000:
            printf("6: set v[0x%X] to 0x%X\n", x, nn);
            break;
        case 0x7000:
            printf("7: Add 0x%X to v[0x%X]\n", nn, x);
        case 0xA000:
            printf("A: Set I to 0x%X\n", instruction & 0x0FFF);
            break;
        default:
            printf("Unknown opcode: %04X\n", instruction);
            break;
    }
}
