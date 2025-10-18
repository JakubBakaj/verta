#ifndef UTILS_C
#define UTILS_C
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define INITIAL_CAPACITY 4

void vector_init(Vector *vec) {
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->data = (void **)malloc(sizeof(void *) * vec->capacity);
}

void vector_push(Vector *vec, void *item) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (void **)realloc(vec->data, sizeof(void *) * vec->capacity);
    }
    vec->data[vec->size++] = item;
}

void *vector_get(Vector *vec, size_t index) {
    if (index < vec->size) {
        return vec->data[index];
    }
    return NULL;
}


void vector_free(Vector *vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

char *read_lines(FILE *file) {
    size_t size = 128;
    size_t dl = 0;
    char *line = (char *)malloc(size);
    if (!line) return NULL;

    int ch;
    while ((ch = fgetc(file)) != EOF) {
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


#endif // UTILS_C