//
// Created by Mikec on 28/10/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
    Token current_token;
    const char *input;
} Parser;

void init_parser(Parser *parser, const char *input);
void advance(Parser *parser);
void expect(Parser *parser, TokenType type);
void parse_program(Parser *parser);
void parse_statement(Parser *parser);
void parse_expression(Parser *parser);
void parse_block(Parser *parser);

#endif //PARSER_H