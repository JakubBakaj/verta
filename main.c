#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UTILS_H
#include "utils.h"
#endif
char *read_lines(FILE *file);
int main(int argc, char *argv[]) {
    // vertac -c input.vrt -o file.elf
    if (argc != 5 || strcmp(argv[1], "-c") != 0 || strcmp(argv[3], "-o") != 0) {
        printf("Usage: %s -c <input_file> -o <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[2], "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file %s\n", argv[2]);
        return 1;
    }

    
    printf("reading file: %s\n", argv[2]);

    char *line;
    int number = 1;
    while ((line = read_lines(inputFile)) != NULL) {
        printf("%4d: %s", number++, line);
        free(line);
    }

    fclose(inputFile);
    return 0;
}
