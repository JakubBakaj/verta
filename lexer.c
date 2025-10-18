#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UTILS_H
#include "utils.h"
#endif

void vector_push(Vector *vec, void *item);

Vector tokenize(const char *source) {
    Vector tokens;
    vector_init(&tokens);

    unsigned int pos = 0;
    size_t length = strlen(source);

    while (pos < length) {
        char current = source[pos];

        // Skip whitespace
        if (isspace(current)) {
            pos++;
            continue;
        }

        Token *token = (Token *)malloc(sizeof(Token));
        token->value = NULL;
        token->pos = pos;

        // Keywords and identifiers
        if (isalpha(current) || current == '_') {
            size_t start = pos;
            while (isalnum(source[pos]) || source[pos] == '_') {
                pos++;
            }
            size_t len = pos - start;
            token->value = (char *)malloc(len + 1);
            strncpy(token->value, &source[start], len);
            token->value[len] = '\0';

            if (strcmp(token->value, "fn") == 0) {
                token->type = TK_KW_FN;
            } else if (strcmp(token->value, "let") == 0) {
                token->type = TK_KW_LET;
            } else if (strcmp(token->value, "ret") == 0) {
                token->type = TK_KW_RET;
            } else {
                token->type = TK_IDENT;
            }
            vector_push(&tokens, token);
            continue;
        }

        // Integer literals
        if (isdigit(current)) {
            size_t start = pos;
            while (isdigit(source[pos])) {
                pos++;
            }
            size_t len = pos - start;
            token->value = (char *)malloc(len + 1);
            strncpy(token->value, &source[start], len);
            token->value[len] = '\0';
            token->type = TK_INT_LITERAL;
            vector_push(&tokens, token);
            continue;
        }

        // Symbols
        switch (current) {
            case '(': token->type = TK_SYM_LPAREN; break;
            case ')': token->type = TK_SYM_RPAREN; break;
            case '{': token->type = TK_SYM_LBRACE; break;
            case '}': token->type = TK_SYM_RBRACE; break;
            case ';': token->type = TK_SYM_SEMI; break;
            case ',': token->type = TK_SYM_COMMA; break;
            case '=': token->type = TK_SYM_ASSIGN; break;
            case '+': token->type = TK_SYM_PLUS; break;
            case '-':
                if (source[pos + 1] == '>') {
                    token->type = TK_ARROW;
                    pos++;
                } else {
                    token->type = TK_SYM_MINUS;
                }
                break;
            case '*': token->type = TK_SYM_ASTERISK; break;
            case '/': token->type = TK_SYM_SLASH; break;
            case ':': token->type = TK_SYM_COLON; break;
            default:
                printf("Unknown character: %c at position %d\n", current, pos);
                free(token);
                pos++;
                continue;
        }
        pos++;
        vector_push(&tokens, token);
    }
    // End of file token
    Token *eofToken = (Token *)malloc(sizeof(Token));
    eofToken->type = TK_EOF;
    eofToken->value = NULL;
    eofToken->pos = pos;
    vector_push(&tokens, eofToken);
    return tokens;
}
