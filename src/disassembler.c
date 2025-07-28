#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/disassembler.h"

void decode_0000(const uint16_t instruction, FILE *output_file) {
    switch (instruction & 0x0FFF) {
        case 0x00E0:
            fprintf(output_file, "clear\n");
            break;
        case 0x00EE:
            fprintf(output_file, "return\n");
            break;
        default:
            break;
    }
}

void decode(const uint8_t *instruction_bytes, FILE *output_file) {
    if (!instruction_bytes) {
        fputs("Error reading instruction\n",stderr);
        exit(EXIT_FAILURE);
    }

    const uint16_t instruction = (unsigned) instruction_bytes[0] << 8 | instruction_bytes[1];

    const uint8_t x = (instruction & 0x0F00) >> 8;
    const uint8_t y = (instruction & 0x00F0) >> 4;
    const uint8_t n = instruction & 0x000F;
    const uint8_t nn = instruction & 0x00FF;
    const uint8_t nnn = instruction & 0x0FFF;

    switch (instruction & 0xF000) {
        case 0x0000:
            decode_0000(instruction, output_file);
            break;
        case 0x1000:
            fprintf(output_file, "jump 0x%X\n", nnn);
            break;
        case 0x3000:
            fprintf(output_file, "if v%X != 0x%X then\n", x, nn);
            break;
        case 0x6000:
            fprintf(output_file, "v%X := 0x%X\n", x, nn);
            break;
        case 0x7000:
            fprintf(output_file, "v%X += 0x%X\n", x, nn);
        case 0x8000:
            // Decode8000()
            break;
        case 0xA000:
            fprintf(output_file, "i := 0x%X\n", nnn);
            break;
        case 0xD000:
            fprintf(output_file, "sprite v%X v%X 0x%X\n", x, y, n);
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

    fprintf(output_file, ": main\n");

    while (fread(buffer, 1, sizeof(buffer), input_file) != 0) {
        uint8_t *instruction_bytes = malloc(sizeof(char) * 2 + 1);
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
