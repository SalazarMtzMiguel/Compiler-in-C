//
// Created by Mikec on 28/10/2024.
//

#include "../include/semantic.h"

#include <parser.h>
#include <string.h>

void init_symbol_table(SymbolTable *table) {
    table->count = 0;
}

int add_symbol(SymbolTable *table, const char *name, TokenType type) {
    if (table->count < 100) {
        strcpy(table->symbols[table->count].name, name);
        table->symbols[table->count].type = type;
        table->count++;
        return 1;
    }
    return 0;
}

TokenType get_symbol_type(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].type;
        }
    }
    return TOKEN_UNKNOWN;
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
            expect(parser, TOKEN_SYMBOL); // Expect ';'
        } else if (strcmp(parser->current_token.value, "if") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // Expect '('
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ')'
            parse_block(parser);
            if (parser->current_token.type == TOKEN_KEYWORD && strcmp(parser->current_token.value, "else") == 0) {
                advance(parser);
                parse_block(parser);
            }
        } else if (strcmp(parser->current_token.value, "while") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // Expect '('
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ')'
            parse_block(parser);
        } else if (strcmp(parser->current_token.value, "for") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // Expect '('
            parse_statement(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ';'
            parse_statement(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ')'
            parse_block(parser);
        } else if (strcmp(parser->current_token.value, "return") == 0) {
            advance(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ';'
        } else if (strcmp(parser->current_token.value, "break") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ';'
        } else if (strcmp(parser->current_token.value, "print") == 0) {
            advance(parser);
            expect(parser, TOKEN_SYMBOL); // Expect '('
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ')'
            expect(parser, TOKEN_SYMBOL); // Expect ';'
        }
    } else if (parser->current_token.type == TOKEN_IDENTIFIER) {
        advance(parser);
        if (parser->current_token.type == TOKEN_OPERATOR && strcmp(parser->current_token.value, "=") == 0) {
            advance(parser);
            parse_expression(parser);
            expect(parser, TOKEN_SYMBOL); // Expect ';'
        }
    }
}