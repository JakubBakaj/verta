#include "ast.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

char* file_name;

Vector parse(Vector *tokens, const char *filename) {
    Vector ast;
    file_name = (char *)filename;
    vector_init(&ast);
    Node *root = (Node *)malloc(sizeof(Node));
    return ast;
}

Token *peek_token(Vector *tokens, size_t offset) {
    if (offset < tokens->size) {
        return (Token *)tokens->data[offset];
    }
    return NULL;
}

Token *consume_token(Vector *tokens, TokenType expected_type, char *error_msg) {
    if (tokens->size == 0) {
        printf("Error: Unexpected end of input. %s\n", error_msg);
        exit(EXIT_FAILURE);
    }

    Token *token = (Token *)tokens->data[0];
    if (token->type != expected_type) {
        printf("Error: Unexpected token '%s' at position %d. %s\n", token->value, token->pos, error_msg);
        exit(EXIT_FAILURE);
    }

    // Remove the token from the vector
    for (size_t i = 1; i < tokens->size; i++) {
        tokens->data[i - 1] = tokens->data[i];
    }
    tokens->size--;

    return token;
}