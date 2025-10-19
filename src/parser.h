#include "utils.h"
#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H
Vector parse(Vector *tokens, const char *filename);
Token *peek_token(Vector *tokens, size_t offset);
Token *consume_token(Vector *tokens, TokenType expected_type, char *error_msg);
#endif // PARSER_H
