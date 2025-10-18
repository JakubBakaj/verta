#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_lines(FILE *plik) {
    size_t size = 128;
    size_t dl = 0;
    char *line = (char *)malloc(size);
    if (!line) return NULL;

    int ch;
    while ((ch = fgetc(plik)) != EOF) {
        if (dl + 1 >= size) {
            size *= 2;
            char *new_ = (char *)realloc(line, size);
            if (!new_) {
                free(line);
                return NULL;
            }
            line = new_;
        }

        line[dl++] = ch;
        if (ch == '\n') break;
    }

    if (dl == 0 && ch == EOF) {
        free(line);
        return NULL;
    }

    line[dl] = '\0';
    return line;
}

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
