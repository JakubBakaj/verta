#include "utils.h"
#include "lexer.h"
#include "ast.h"
#include <string.h>
#ifndef PARSER_H
#define PARSER_H
Vector parse(Vector *tokens, const char *filename);
Token *peek_token(Vector *tokens, size_t offset);
Token consume_token(Vector *tokens, TokenType expected_type, char error_msg[]);
void advance();
Node *parse_fn(Vector* tokens);
Node parse_type(Vector* tokens);
Node *parse_body(Vector* tokens);
Node *parse_stmt(Vector* tokens);
Node *parse_return(Vector* tokens);
Node parse_expr(Vector* tokens);
#endif // PARSER_H
