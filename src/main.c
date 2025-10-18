#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UTILS_H
#include "utils.h"
#endif

#ifndef LEXER_H
#include "lexer.h"
#endif

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

    // Read entire file into a single buffer for tokenization
    fseek(inputFile, 0, SEEK_END);
    long file_size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *source = (char *)malloc(file_size + 1);
    if (!source) {
        fprintf(stderr, "Error: could not allocate buffer for input file\n");
        fclose(inputFile);
        return 1;
    }
    size_t read = fread(source, 1, file_size, inputFile);
    source[read] = '\0';

    
    // Tokenize the file
    Vector tokens = tokenize(source);
    for (size_t i = 0; i < tokens.size; i++) {
        Token *token = (Token *)vector_get(&tokens, i);
        if (token) {
            printf("Token Type: %d, Value: %s, Position: %u\n", token->type, token->value ? token->value : "NULL", token->pos);
            free(token->value);
            free(token);
        }
    }
    vector_free(&tokens);
    free(source);

    fclose(inputFile);
    return 0;
}
