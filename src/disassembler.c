#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/disassembler.h"

void decode_0000(const unsigned short instruction, FILE *output_file) {
    switch (instruction & 0x0FFF) {
        case 0x00E0:
            fprintf(output_file, "0x%04X: Clear the screen\n", instruction);
            // printf("0x%04X: Clear the screen\n", instruction);
            break;
        case 0x00EE:
            fprintf(output_file, "0x%04X: Return from subroutine to address pulled from stack\n", instruction);
            // printf("0x%04X: Return from subroutine to address pulled from stack\n", instruction);
            break;
        default:
            break;
    }
}

void decode(const unsigned char *instruction_bytes, FILE *output_file) {
    if (!instruction_bytes) {
        fputs("Error reading instruction\n",stderr);
        exit(EXIT_FAILURE);
    }

    if (!output_file) {
        fputs("I/O error\n",stderr);
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
            decode_0000(instruction, output_file);
            break;
        case 0x6000:
            printf("6: set v[0x%X] to 0x%X\n", x, nn);
            fprintf(output_file, "6: set v[0x%X] to 0x%X\n", x, nn);
            break;
        case 0x7000:
            printf("7: Add 0x%X to v[0x%X]\n", nn, x);
        //  fprintf(f, "7: Add 0x%X to v[0x%X]\n", nn, x);
        case 0xA000:
            printf("A: Set I to 0x%X\n", instruction & 0x0FFF);
            break;
        default:
            printf("Unknown opcode: %04X\n", instruction);
            break;
    }
}

void disassemble(const char *filename, const char *out_filename) {
    unsigned char buffer[2];
    FILE *input_file = fopen(filename, "rb");

    if (!input_file) {
        fputs("Error reading file\n",stderr);
        exit(EXIT_FAILURE);
    }

    FILE *output_file = fopen(out_filename, "a");

    if (!output_file) {
        fputs("Error writing output to file\n",stderr);
        exit(EXIT_FAILURE);
    }

    while (fread(buffer, 1, sizeof(buffer), input_file) != 0) {
        unsigned char *instruction_bytes = malloc(sizeof(char) * 2 + 1);
        memcpy(instruction_bytes, buffer, 2);
        decode(instruction_bytes, output_file);
        free(instruction_bytes);
    }

    if (ferror(input_file)) {
        fputs("I/O error while reading file\n",stderr);
        exit(EXIT_FAILURE);
    }

    if (feof(input_file)) {
        printf("End of file was reached successfully");
        fclose(input_file);
    }

    fclose(output_file);
}
