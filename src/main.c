#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/filehelpers.h"
#include "../include/disassembler.h"

int main(const int argc, char *argv[]) {
    if (argc == 2) {
        // get_filepath should create its own string, then the
        // caller code will be clearer: it needs two frees to
        // free both strings
        char *working_directory = get_working_directory();
        char *filepath = get_filepath(working_directory, argv[1]);

        disassemble(filepath);
        free(working_directory);
        free(filepath);

        return 0;
    }

    printf("Usage: ./ChipDecode file.ch8\n");
    printf("Ensure that CHIP-8 ROM is in the same directory as ChipDecode.");

    return 1;
}
