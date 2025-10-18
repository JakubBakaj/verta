#ifndef LEXER_H
#define LEXER_H

#include "utils.h"

typedef enum {
    //keywords
    TK_KW_FN,
    TK_KW_LET,
    TK_KW_RET,
    TK_KW_EXT,
    TK_KW_CONST,

    //symbols
    TK_SYM_LPAREN,   // (
    TK_SYM_RPAREN,   // )
    TK_SYM_LBRACE,   // {
    TK_SYM_RBRACE,   // }
    TK_SYM_SEMI,     // ;
    TK_SYM_COMMA,    // ,
    TK_SYM_ASSIGN,   // =
    TK_SYM_PLUS,     // +
    TK_SYM_MINUS,    // -
    TK_SYM_ASTERISK, // *
    TK_SYM_SLASH,    // /
    TK_SYM_COLON,    // :

    //identifiers and literals
    TK_IDENT,
    TK_INT_LITERAL,
    TK_EOF,
    //others
    TK_ARROW,       // ->
    TK_VARARG,      // ...
} TokenType;


typedef struct {
    TokenType type;
    char *value;
    unsigned int pos;
} Token;

// Tokenize the given source string and return a Vector of Token*.
Vector tokenize(const char *source);
#endif // LEXER_H