#include "ast.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>

char* file_name;
size_t token_index = 0;

Vector parse(Vector *tokens, const char *filename) {
    Vector ast;
    file_name = (char *)filename;
    vector_init(&ast);
    Node *root = (Node *)malloc(sizeof(Node));
    if(!root) {
        fprintf(stderr, "Error: could not allocate memory for AST root node\n");
        exit(EXIT_FAILURE);
    }
    root->type = ND_PROGRAM;
    vector_init(&root->children);
    vector_push(&ast, root);

    return ast;
}

Node parse_stmt(Vector* tokens) {
        Token *current = peek_token(tokens, 0);
    if( current == NULL) {
        fprintf(stderr, "Error: No tokens to parse in file %s\n", file_name);
        exit(EXIT_FAILURE);
    } else if(current->type == TK_EOF) {
        fprintf(stderr, "Error: Empty input file %s\n", file_name);
        exit(EXIT_FAILURE);
    }else if(current->type == TK_KW_FN) {
        parse_fn(tokens);
    } else {
        LineCol lc = get_line_col(read_lines(file_name), current->pos);
        fprintf(stderr, "Error: Unexpected token '%s' at <%d, %d> in file %s\n", current->value, lc.line,lc.column, file_name);
        exit(EXIT_FAILURE);
    }
}

Node parse_fn(Vector* tokens) {
    advance();
    char* name = consume_token(tokens, TK_IDENT, "Expected function name after 'fn'").value;
    consume_token(tokens, TK_SYM_LPAREN, "Expected '(' after function name");
    //TODO: parse parameters
    consume_token(tokens, TK_SYM_RPAREN, "Expected ')' after function parameters");
    parse_body(tokens);
}

Vector *parse_body(Vector* tokens) {
    Vector body;
    vector_init(&body);
    consume_token(tokens, TK_SYM_LBRACE, "Expected '{'");
    for(;;){
        Token *current = peek_token(tokens, 0);
        if(current == NULL) {
            fprintf(stderr, "Error: Unexpected end of tokens in function body in file %s\n", file_name);
            exit(EXIT_FAILURE);
        } else if(current->type == TK_SYM_RBRACE) {
            advance();
            break;
        } else {
            Node stmt = parse_stmt(tokens);
            vector_push(&body, &stmt);
        }
    }
    return &body;
}

Token *peek_token(Vector *tokens, size_t offset) {
    if (offset < tokens->size) {
        return (Token *)tokens->data[offset];
    }
    return NULL;
}

Token consume_token(Vector *tokens, TokenType expected_type, char *error_msg) {
    Token *token = peek_token(tokens, token_index);
    if (token == NULL || token->type != expected_type) {
        LineCol lc = get_line_col(read_lines(file_name), token ? token->pos : 0);
        fprintf(stderr, "Error: %s at <%d, %d> in file %s\n", error_msg, lc.line, lc.column, file_name);
        exit(EXIT_FAILURE);
    }
    token_index++;
    return *token;
}

void advance(){
    token_index++;
}