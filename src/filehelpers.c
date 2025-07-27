#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/filehelpers.h"

// We can't return an array here, so we must return a pointer
// to an array.
char *get_working_directory(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        // Returns a pointer to a null-terminated byte string,
        // which is a duplicate of the string pointed to by str1.
        // The returned pointer must be passed to free to avoid a memory leak.
        // If an error occurs, a null pointer is returned and errno may be set.
        char *working_dir = strdup(cwd);

        if (working_dir == NULL) {
            fputs("Error getting working directory\n",stderr);
            exit(EXIT_FAILURE);
        }

        return working_dir;
    }

    fputs("Error getting working directory\n",stderr);
    exit(EXIT_FAILURE);
}

// Don't use strcat() to concatenate the directory and filename
// because it's appending to the first string. The first strcat
// would immediately write out of bounds because strdup() allocates
// just enough to hold the string.
char *get_filepath(const char *working_directory, const char *filename) {
    size_t directory_length = strlen(working_directory);
    size_t filename_length = strlen(filename);

    if(directory_length >= SIZE_MAX - filename_length || directory_length + filename_length + 1 == SIZE_MAX)
    {
        fputs("Error: Directory length exceeds max size.\n",stderr);
        exit(EXIT_FAILURE);
    }

    char *result = malloc(directory_length + filename_length + 2);

    if(!result){
        fputs("Error allocating filepath memory.\n",stderr);
        exit(EXIT_FAILURE);
    }

    memcpy(result, working_directory, directory_length);

    // directory_length is the position of the null terminator
    result[directory_length] = '/';

    memcpy(result + directory_length + 1, filename, filename_length);

    // Add the null terminator at the end
    result[directory_length + filename_length + 1] = 0;

    return result;
}
