#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filehelpers.h"

char *generate_output_filename(const char *filename) {
    const char *file_extension = strrchr(filename, '.');
    const char *output_extension = ".txt";
    const size_t filename_length = file_extension - filename;
    const size_t extension_length = strlen(output_extension);

    char *output_filename = malloc(filename_length + extension_length + 1);

    if(!output_filename){
        fputs("Error allocating filepath memory.\n",stderr);
        exit(EXIT_FAILURE);
    }

    memcpy(output_filename, filename, filename_length);
    memcpy(output_filename + filename_length, output_extension, extension_length + 1);

    output_filename[filename_length + extension_length + 1] = 0;

    printf("Extension File: %s\n", output_filename);
    return output_filename;
}

void clear_output_file(const char *filename) {
    FILE *output_file = fopen(filename, "w");
    if (!output_file)
    {
        fputs("Error opening file\n",stderr);
        exit(EXIT_FAILURE);
    }

    fclose(output_file);
}
