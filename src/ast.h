#ifndef AST_H
#define AST_H
#include "utils.h"
#include <stdbool.h>
typedef enum{
    ND_FN_DECL,
    ND_VAR_DECL,
    ND_CONST_DECL,
    ND_BLOCK_STMT,
    ND_EXPR_STMT,
    ND_RETURN_STMT,
    ND_BINARY_EXPR,
    ND_UNARY_EXPR,
    ND_INT_LITERAL,
    ND_STRING_LITERAL,
    ND_IDENT_EXPR,
    ND_CALL_EXPR,
    ND_PROGRAM
} NodeType;

typedef enum {
    TYPE_I32,
    TYPE_I64,
    TYPE_U8
} types;

typedef struct {
    NodeType kind;
    Vector children;
    __int64_t int_value;
    char* str_value;
    bool is_pointer;
    types type;
} Node;

#endif // AST_H
