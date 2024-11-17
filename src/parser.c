//
// Created by Mikec on 28/10/2024.
//

#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>

void init_parser(Parser *parser, const char *input) {
    parser->input = input;
    parser->current_token = get_next_token(&parser->input);
}

void advance(Parser *parser) {
    parser->current_token = get_next_token(&parser->input);
}

void expect(Parser *parser, TokenType type) {
    if (parser->current_token.type != type) {
        fprintf(stderr, "Syntax error: expected token type %d, got %d\n", type, parser->current_token.type);
        exit(1);
    }
    advance(parser);
}

void parse_program(Parser *parser) {
    while (parser->current_token.type != TOKEN_UNKNOWN) {
        parse_statement(parser);
    }
}

void parse_statement(Parser *parser) {
    if (parser->current_token.type == TOKEN_KEYWORD) {
        if (strcmp(parser->current_token.value, "int") == 0 || strcmp(parser->current_token.value, "char") == 0) {
            advance(parser);
            expect(parser, TOKEN_IDENTIFIER);
            if (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "=") == 0) {
                advance(parser);
                parse_expression(parser);
            }
            expect(parser, TOKEN_SYMBOL);
        } else if (strcmp(parser->current_token.value, "if") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_block(parser);
            if (parser->current_token.type == TOKEN_KEYWORD && strcmp(parser->current_token.value, "else") == 0) {
                advance(parser);
                parse_block(parser);
            }
        } else if (strcmp(parser->current_token.value, "while") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_block(parser);
        } else if (strcmp(parser->current_token.value, "for") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_statement(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_statement(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_block(parser);
        } else if (strcmp(parser->current_token.value, "return") == 0) {
            advance(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
        } else if (strcmp(parser->current_token.value, "break") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL);
        } else if (strcmp(parser->current_token.value, "print") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
        }
    } else if (parser->current_token.type == TOKEN_IDENTIFIER) {
        advance(parser);
        if (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "=") == 0) {
            advance(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL);
        }
    }
}
/*
void parse_expression(Parser *parser) {
    // Implementar la lógica para analizar expresiones
    // Esto puede incluir llamadas recursivas para manejar operadores y paréntesis
    advance(parser);
}*/
void parse_expression(Parser *parser) {
    // Example implementation for parsing a simple expression
    if (parser->current_token.type == TOKEN_IDENTIFIER || parser->current_token.type == TOKEN_NUMBER) {
        advance(parser);
        if (parser->current_token.type == TOKEN_OPERATOR) {
            advance(parser);
            parse_expression(parser);
        }
    } else {
        fprintf(stderr, "Syntax error: unexpected token %s\n", parser->current_token.value);
        exit(1);
    }
}

void parse_block(Parser *parser) {
    expect(parser, TOKEN_SYMBOL);
    while (parser->current_token.type != TOKEN_SYMBOL) {
        parse_statement(parser);
    }
    expect(parser, TOKEN_SYMBOL);
}