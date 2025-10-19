#ifndef AST_H
#define AST_H
#include "utils.h"
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
} NodeType;

typedef struct {
    NodeType type;
    Vector children;
} Node;

#endif // AST_H
