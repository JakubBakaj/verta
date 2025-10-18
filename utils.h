#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
typedef struct
{
    void **data;
    size_t size;
    size_t capacity;
} Vector; //replacement for C++ std::vector

void vector_init(Vector *vec);
void vector_push_back(Vector *vec, void *value);
void vector_free(Vector *vec);
void vector_get(Vector *vec, size_t index);

#endif // UTILS_H