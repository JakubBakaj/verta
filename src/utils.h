#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <stdio.h>
typedef struct
{
    void **data;
    size_t size;
    size_t capacity;
} Vector; //replacement for C++ std::vector

typedef struct
{
    unsigned int line;
    unsigned int column;
} LineCol;

void vector_init(Vector *vec);
void vector_push(Vector *vec, void *item);
void *vector_get(Vector *vec, size_t index);
void vector_free(Vector *vec);

// Read a single line (including '\n') from FILE. Returns a heap-allocated
// NUL-terminated string which must be freed by the caller. Returns NULL on EOF
// or allocation error.
char *read_lines(char *file_path);
LineCol get_line_col(const char *source, size_t pos);

#endif // UTILS_H