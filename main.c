#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "filehelpers.h"

void read_file(const char *filename) {
    unsigned char buffer[2];
    FILE *file = fopen(filename, "rb");

    if (file)
    {
        while (fread(buffer, 1, sizeof(buffer), file) != 0)
        {
            printf("Buffer [0]: %04X Buffer[1]: %04X\n", buffer[0], buffer[1]);
        }

        if (ferror(file)) {
            fputs("I/O error while reading file\n",stderr);
        }

        else if (feof(file)) {
            printf("End of file was reached successfully");
            fclose(file);
        }
    }

    else {
        fputs("Error reading file\n",stderr);
        exit(EXIT_FAILURE);
    }
}
/*
void decode(const unsigned char *instruction) {
    const unsigned char opcode = instruction[0] | 0x00F0;
    printf("Opcode: %c\n", opcode);

    const unsigned short instruction = (unsigned) buffer[0] << 8 | buffer[1];
    printf("Instruction: %04X\n", instruction);

    switch (instruction & 0xF000) {
        case 0x0000:
            switch (instruction & 0x00F0) {
            case 0x00E0:
                    printf("Opcode 00E0 detected\n");
                    break;
            default:
                    printf("Unknown opcode: %04X\n", instruction);
                    break;
            }
            break;
        default:
            printf("Unknown opcode x\n");
            break;
    }
} */

int main(const int argc, char *argv[]) {
    if (argc == 2) {
        // get_filepath should create its own string, then the
        // caller code will be clearer: it needs two frees to
        // free both strings
        char *working_directory = get_working_directory();
        char *filepath = get_filepath(working_directory, argv[1]);
        printf("Filepath: %s\n", filepath);

        read_file(filepath);

        free(working_directory);
        free(filepath);

        return 0;
    }

    printf("Usage: ./ChipDecode file.ch8\n");
    printf("Ensure that CHIP-8 ROM is in the same directory as ChipDecode.");

    return 1;
}
