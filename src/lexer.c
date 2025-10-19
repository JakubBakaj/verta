#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef UTILS_H
#include "utils.h"
#endif

void vector_push(Vector *vec, void *item);

Vector tokenize(const char *source, const char *filename) {
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
            } else if(strcmp(token->value, "ext") == 0) {
                token->type = TK_KW_EXT;
            } else if(strcmp(token->value, "const") == 0) {
                token->type = TK_KW_CONST;
            }
            else {
                token->type = TK_IDENT;
            }
            vector_push(&tokens, token);
            continue;
        }else if (isdigit(current)) {
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
        } else if(current == '.' && source[pos + 1] == '.' && source[pos + 2] == '.')/*ther should be check if pos + 1 etc exsists*/ {
            token->type = TK_VARARG;
            token->value = (char *)malloc(4);
            strcpy(token->value, "...");
            pos += 2;
        }
        else if(current == '\"') {
            // String literal
            size_t start = pos + 1; // skip opening quote
            pos++;
            while (source[pos] != '\"' && pos < length) {
                // Handle escape sequences
                if (source[pos] == '\\' && pos + 1 < length) {
                    pos += 2; // skip escaped character
                } else {
                    pos++;
                }
            }
            size_t len = pos - start;
            token->value = (char *)malloc(len + 1);
            strncpy(token->value, &source[start], len);
            token->value[len] = '\0';
            token->type = TK_STRING_LITERAL;
        }
else {
    // Symbols
    switch (current) {
        case '(': 
            token->type = TK_SYM_LPAREN;
            token->value = (char *)malloc(2);
            strcpy(token->value, "(");
            break;
        case ')': 
            token->type = TK_SYM_RPAREN;
            token->value = (char *)malloc(2);
            strcpy(token->value, ")");
            break;
        case '{': 
            token->type = TK_SYM_LBRACE;
            token->value = (char *)malloc(2);
            strcpy(token->value, "{");
            break;
        case '}': 
            token->type = TK_SYM_RBRACE;
            token->value = (char *)malloc(2);
            strcpy(token->value, "}");
            break;
        case ';': 
            token->type = TK_SYM_SEMI;
            token->value = (char *)malloc(2);
            strcpy(token->value, ";");
            break;
        case ',': 
            token->type = TK_SYM_COMMA;
            token->value = (char *)malloc(2);
            strcpy(token->value, ",");
            break;
        case '=': 
            token->type = TK_SYM_ASSIGN;
            token->value = (char *)malloc(2);
            strcpy(token->value, "=");
            break;
        case '+': 
            token->type = TK_SYM_PLUS;
            token->value = (char *)malloc(2);
            strcpy(token->value, "+");
            break;
        case '-':
            if (source[pos + 1] == '>') {
                token->type = TK_ARROW;
                token->value = (char *)malloc(3);
                strcpy(token->value, "->");
                pos++;
            } else {
                token->type = TK_SYM_MINUS;
                token->value = (char *)malloc(2);
                strcpy(token->value, "-");
            }
            break;
        case '*': 
            token->type = TK_SYM_ASTERISK;
            token->value = (char *)malloc(2);
            strcpy(token->value, "*");
            break;
        case '/': 
            token->type = TK_SYM_SLASH;
            token->value = (char *)malloc(2);
            strcpy(token->value, "/");
            break;
        case ':': 
            token->type = TK_SYM_COLON;
            token->value = (char *)malloc(2);
            strcpy(token->value, ":");
            break;
        default:
            printf("Unknown character: %c at position %d\n", current, pos);
            free(token);
            pos++;
            continue;
    }
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
