#include "ast.h"
#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

char* file_name;
size_t token_index = 0;

Vector parse(Vector *tokens, const char *filename) {
    printf("Parsing tokens from file: %s\n", filename);
    Vector ast;
    file_name = (char *)filename;
    vector_init(&ast);
    Node *root = (Node *)malloc(sizeof(Node));
    if(!root) {
        fprintf(stderr, "Error: could not allocate memory for AST root node\n");
        exit(EXIT_FAILURE);
    }
    root->kind = ND_PROGRAM;
    vector_init(&root->children);
    vector_push(&ast, root);
    while (token_index < tokens->size) {
        Node *stmt = (Node *)malloc(sizeof(Node));
        if(!stmt) {
            fprintf(stderr, "Error: could not allocate memory for statement node in file %s\n", file_name);
            exit(EXIT_FAILURE);
        }
        stmt = parse_stmt(tokens);
        vector_push(&root->children, stmt);
    }
    return ast;
}

Node *parse_stmt(Vector* tokens) {
        Token *current = peek_token(tokens, 0);
    if( current == NULL) {
        fprintf(stderr, "Error: No tokens to parse in file %s\n", file_name);
        exit(EXIT_FAILURE);
    } else if(current->type == TK_EOF) {
        fprintf(stderr, "Error: Empty input file %s\n", file_name);
        exit(EXIT_FAILURE);
    }else if(current->type == TK_KW_FN) {
        return parse_fn(tokens);
    } else {
        LineCol lc = get_line_col(read_lines(file_name), current->pos);
        fprintf(stderr, "Error: Unexpected token '%d' at <%d, %d> in file %s\n", current->type, lc.line,lc.column, file_name);
        exit(EXIT_FAILURE);
    }
}

Node *parse_fn(Vector* tokens) {
    Node *fn_node = (Node *)malloc(sizeof(Node));
    if(!fn_node) {
        fprintf(stderr, "Error: could not allocate memory for function node in file %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    fn_node->kind = ND_FN_DECL;
    vector_init(&fn_node->children);
    advance();
    char* name = consume_token(tokens, TK_IDENT, "Expected function name after 'fn'").value;
    consume_token(tokens, TK_SYM_LPAREN, "Expected '(' after function name");
    //TODO: parse parameters
    consume_token(tokens, TK_SYM_RPAREN, "Expected ')' after function parameters");
    vector_push(&fn_node->children, parse_body(tokens));
    return fn_node;
}

Vector *parse_body(Vector* tokens) {
    Vector *body = (Vector *)malloc(sizeof(Vector));
    vector_init(body);
    consume_token(tokens, TK_SYM_LBRACE, "Expected '{'");
    for(;;){
        Token *current = peek_token(tokens, 0);
        if(current == NULL) {
            fprintf(stderr, "Error: Unexpected end of tokens in file %s\n", file_name);
            exit(EXIT_FAILURE);
        } else if(current->type == TK_SYM_RBRACE) {
            advance();
            break;
        } else {
            Node *stmt = (Node *)malloc(sizeof(Node));
            if(!stmt) {
                fprintf(stderr, "Error: could not allocate memory for statement node in file %s\n", file_name);
                exit(EXIT_FAILURE);
            }
            stmt = parse_stmt(tokens);
            vector_push(body, stmt);
        }
    }
    return body;
}


Node *parse_return(Vector* tokens) {
    Node *return_node = (Node *)malloc(sizeof(Node));
    if(!return_node) {
        fprintf(stderr, "Error: could not allocate memory for return node in file %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    return_node->kind = ND_RETURN_STMT;
    vector_init(&return_node->children);
    advance();
    Node *expr = (Node *)malloc(sizeof(Node));
    if(!expr) {
        fprintf(stderr, "Error: could not allocate memory for return expression node in file %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    *expr = parse_expr(tokens);
    vector_push(&return_node->children, expr);
    consume_token(tokens, TK_SYM_SEMI, "Expected ';' after return statement");
    return return_node;
}

Node parse_expr(Vector* tokens) {
    Token *current = peek_token(tokens, 0);
    if(current == NULL) {
        fprintf(stderr, "Error: Unexpected end of tokens in file %s\n", file_name);
        exit(EXIT_FAILURE);
    }
    if(current->type == TK_INT_LITERAL) {
        Node int_node;
        int_node.kind = ND_INT_LITERAL;
        int_node.int_value = atoll(current->value);
        vector_init(&int_node.children);
        advance();
        return int_node;
    } else if(current->type == TK_STRING_LITERAL) {
        Node str_node;
        str_node.kind = ND_STRING_LITERAL;
        str_node.str_value = current->value;
        vector_init(&str_node.children);
        advance();
        return str_node;
    } else {
        LineCol lc = get_line_col(read_lines(file_name), current->pos);
        fprintf(stderr, "Error: Unexpected token '%s' at <%d, %d> in file %s\n", current->value, lc.line,lc.column, file_name);
        exit(EXIT_FAILURE);
    }
}

Token *peek_token(Vector *tokens, size_t offset) {
    size_t idx = token_index + offset;
    if (idx < tokens->size) {
        return (Token *)tokens->data[idx];
    }
    return NULL;
}


Token consume_token(Vector *tokens, TokenType expected_type, char error_msg[]) {
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