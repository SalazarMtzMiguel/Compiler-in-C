#include "../include/lexer.h"
#include "../include/semantic.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int", "char", "if", "else", "while", "for", "return", "void", "print", "hola"};
const char *operators[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "="};
const char *symbols[] = {"{", "}", "(", ")", "[", "]", ";", ","};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))
#define OPERATOR_COUNT (sizeof(operators) / sizeof(operators[0]))
#define SYMBOL_COUNT (sizeof(symbols) / sizeof(symbols[0]))

int is_keyword(const char *str) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *str) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (strcmp(str, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_symbol(const char *str) {
    for (int i = 0; i < SYMBOL_COUNT; i++) {
        if (strcmp(str, symbols[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token get_next_token(const char **input) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    while (isspace(**input)) (*input)++;

    if (isalpha(**input) || **input == '_') {
        int length = 0;
        while (isalnum(**input) || **input == '_') {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = is_keyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
    } else if (isdigit(**input)) {
        int length = 0;
        while (isdigit(**input)) {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_NUMBER;
    } else if (**input == '\'') {
        if (**input == '\'' && *(*input + 2) == '\'') {
            token.value[0] = *(*input)++;
            token.value[1] = *(*input)++;
            token.value[2] = *(*input)++;
            token.value[3] = '\0';
            token.type = TOKEN_CHAR;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
    } else if (**input == '\"') {
        int length = 0;
        token.value[length++] = *(*input)++;
        while (**input != '\"' && **input != '\0') {
            token.value[length++] = *(*input)++;
        }
        if (**input == '\"') {
            token.value[length++] = *(*input)++;
            token.value[length] = '\0';
            token.type = TOKEN_STRING;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
    } else {
        char op[3] = {0};
        op[0] = *(*input)++;
        op[1] = **input;
        op[2] = '\0';

        if (is_operator(op)) {
            token.type = TOKEN_OPERATOR;
            (*input)++;
        } else if (is_symbol(op)) {
            token.type = TOKEN_SYMBOL;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
        strcpy(token.value, op);
    }

    return token;
}