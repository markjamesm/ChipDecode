#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/filehelpers.h"
#include "../include/disassembler.h"

int main(const int argc, char *argv[]) {
    if (argc == 2) {
        const char *filename = argv[1];
        char *output_filename = generate_output_filename(filename);

        clear_output_file(output_filename);
        disassemble(filename, output_filename);
        free(output_filename);

        return 0;
    }

    printf("Usage: ./ChipDecode file.ch8\n");
    printf("Ensure that CHIP-8 ROM is in the same directory as ChipDecode.");

    return 1;
}
