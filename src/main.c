#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/filehelpers.h"
#include "../include/decoder.h"

void read_file(const char *filename) {
    unsigned char buffer[2];
    FILE *file = fopen(filename, "rb");

    if (file)
    {
        while (fread(buffer, 1, sizeof(buffer), file) != 0)
        {
            unsigned char *instruction_bytes = malloc(sizeof(char) * 2 + 1);
            memcpy(instruction_bytes, buffer, 2);

            decode(instruction_bytes);
            free(instruction_bytes);
        }

        if (ferror(file)) {
            fputs("I/O error while reading file\n",stderr);
            exit(EXIT_FAILURE);
        }

        if (feof(file)) {
            printf("End of file was reached successfully");
            fclose(file);
        }
    }

    else {
        fputs("Error reading file\n",stderr);
        exit(EXIT_FAILURE);
    }
}

int main(const int argc, char *argv[]) {
    if (argc == 2) {
        // get_filepath should create its own string, then the
        // caller code will be clearer: it needs two frees to
        // free both strings
        char *working_directory = get_working_directory();
        char *filepath = get_filepath(working_directory, argv[1]);

        read_file(filepath);
        free(working_directory);
        free(filepath);

        return 0;
    }

    printf("Usage: ./ChipDecode file.ch8\n");
    printf("Ensure that CHIP-8 ROM is in the same directory as ChipDecode.");

    return 1;
}
