#include <stdio.h>
#include <stdlib.h>

#include "../include/decoder.h"

void decode_0000(const unsigned short instruction) {
    switch (instruction & 0x0FFF) {
        case 0x00E0:
            printf("%04X detected: Clear the screen\n", instruction);
            break;
        case 0x00EE:
            printf("%04X detected: Return from subroutine to address pulled from stack\n", instruction);
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

    switch (instruction & 0xF000) {
        case 0x0000:
            decode_0000(instruction);
            break;
        case 0xA000:
            printf("Opcode A: Set I to %03X\n", instruction & 0x0FFF);
            break;
        default:
            printf("Unknown opcode: %04X\n", instruction);
            break;
    }
}
