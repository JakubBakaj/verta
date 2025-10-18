#ifndef UTILS_C
#define UTILS_C
#include "utils.h"
#include <stdlib.h>
#include <string.h>
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

#endif // UTILS_C