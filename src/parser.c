// parser.c

#include "parser.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa el parser con la entrada proporcionada
// Parametros:
// - parser: puntero al parser
// - input: cadena de entrada
void init_parser(Parser *parser, const char *input) {
    parser->input = input;
    parser->current_token = get_next_token(&parser->input);
    log_message("Parser inicializado con entrada: %s", input);
}

// Avanza al siguiente token en la entrada
// Parametros:
// - parser: puntero al parser
void advance(Parser *parser) {
    parser->current_token = get_next_token(&parser->input);
    log_message("Avanzado al siguiente token: %s", parser->current_token.value);
}

// Verifica que el token actual sea del tipo esperado y avanza
// Parametros:
// - parser: puntero al parser
// - type: tipo de token esperado
void expect(Parser *parser, TokenType type) {
    if (parser->current_token.type != type) {
        log_message("Error de sintaxis: se esperaba el tipo de token %d, se obtuvo %d", type, parser->current_token.type);
        fprintf(stderr, "Error de sintaxis: se esperaba el tipo de token %d, se obtuvo %d\n", type, parser->current_token.type);
        exit(1);
    }
    advance(parser);
}

// Parsea el programa completo
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST del programa
ASTNode* parse_program(Parser *parser) {
    ASTNode *program = create_ast_node(AST_PROGRAM, parser->current_token);
    log_message("Parseando programa");
    while (parser->current_token.type != TOKEN_UNKNOWN) {
        ASTNode *statement = parse_statement(parser);
        // Aqui puedes agregar el statement al programa (por ejemplo, a una lista de statements)
        advance(parser);
    }
    return program;
}

// Parsea una declaracion
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST de la declaracion
ASTNode* parse_statement(Parser *parser) {
    ASTNode *statement = create_ast_node(AST_STATEMENT, parser->current_token);
    log_message("Parseando declaracion: %s", parser->current_token.value);
    if (parser->current_token.type == TOKEN_KEYWORD) {
        if (strcmp(parser->current_token.value, "int") == 0 || strcmp(parser->current_token.value, "char") == 0 || strcmp(parser->current_token.value, "string") == 0) {
            advance(parser);
            expect(parser, TOKEN_IDENTIFIER);
            if (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "=") == 0) {
                advance(parser);
                statement->left = parse_expression(parser);
            }
            expect(parser, TOKEN_SYMBOL);
        } else if (strcmp(parser->current_token.value, "if") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // '('
            statement->left = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // ')'
            statement->right = parse_block(parser);
            if (parser->current_token.type == TOKEN_KEYWORD && strcmp(parser->current_token.value, "else") == 0) {
                advance(parser);
                statement->right->right = parse_block(parser);
            }
        } else if (strcmp(parser->current_token.value, "while") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // '('
            statement->left = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // ')'
            statement->right = parse_block(parser);
        } else if (strcmp(parser->current_token.value, "return") == 0) {
            advance(parser);
            statement->left = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // ';'
        } else if (strcmp(parser->current_token.value, "print") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // '('
            statement->left = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // ')'
            expect(parser, TOKEN_SYMBOL); // ';'
        } else if (strcmp(parser->current_token.value, "main") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // '('
            expect(parser, TOKEN_SYMBOL); // ')'
            statement->left = parse_block(parser);
        }
    } else if (parser->current_token.type == TOKEN_IDENTIFIER) {
        advance(parser);
        if (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "=") == 0) {
            advance(parser);
            statement->left = parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // ';'
        }
    } else {
        advance(parser);
    }
    return statement;
}

// Parsea una expresion
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST de la expresion
ASTNode* parse_expression(Parser *parser) {
    ASTNode *expression = create_ast_node(AST_EXPRESSION, parser->current_token);
    log_message("Parseando expresion: %s", parser->current_token.value);
    if (parser->current_token.type == TOKEN_IDENTIFIER ||
        parser->current_token.type == TOKEN_NUMBER ||
        parser->current_token.type == TOKEN_STRING) {
        advance(parser);
        if (parser->current_token.type == TOKEN_OPERATOR) {
            expression->left = create_ast_node(AST_LITERAL, parser->current_token);
            advance(parser);
            expression->right = parse_expression(parser);
        }
    } else {
        fprintf(stderr, "Error de sintaxis: token inesperado %s\n", parser->current_token.value);
        exit(1);
    }
    return expression;
}

// Parsea un bloque de codigo
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST del bloque
ASTNode* parse_block(Parser *parser) {
    expect(parser, TOKEN_SYMBOL);
    ASTNode *block = create_ast_node(AST_BLOCK, parser->current_token);
    log_message("Parseando bloque");
    while (parser->current_token.type != TOKEN_SYMBOL) {
        ASTNode *statement = parse_statement(parser);
        // Aqui puedes agregar el statement al bloque (por ejemplo, a una lista de statements)
    }
    expect(parser, TOKEN_SYMBOL);
    return block;
}