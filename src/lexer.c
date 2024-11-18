#include "../include/lexer.h"
#include "../include/semantic.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// List of recognized keywords
const char *keywords[] = {"int", "char", "if", "else", "while", "for", "return", "void", "print", "break", "input"};

// List of recognized operators
const char *operators[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "="};

// List of recognized symbols
const char *symbols[] = {"{", "}", "(", ")", "[", "]", ";", ","};

// Constants to calculate the number of elements in each list
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

    // Skip whitespace
    while (isspace(**input)) (*input)++;

    // Identify single-character symbols
    char symbol[2] = {*(*input), '\0'};
    if (is_symbol(symbol)) {
        token.value[0] = *(*input)++;
        token.value[1] = '\0';
        token.type = TOKEN_SYMBOL;
        return token;
    }

    // Identify operators (one or two characters)
    char op[3] = {*(*input), *(*input + 1), '\0'};
    if (is_operator(op)) {
        token.value[0] = *(*input)++;
        token.value[1] = *(*input)++;
        token.value[2] = '\0';
        token.type = TOKEN_OPERATOR;
        return token;
    } else {
        op[1] = '\0';
        if (is_operator(op)) {
            token.value[0] = *(*input)++;
            token.value[1] = '\0';
            token.type = TOKEN_OPERATOR;
            return token;
        }
    }

    // Identify keywords or identifiers
    if (isalpha(**input) || **input == '_') {
        int length = 0;
        while (isalnum(**input) || **input == '_') {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = is_keyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    }

    // Identify numbers
    if (isdigit(**input)) {
        int length = 0;
        while (isdigit(**input)) {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Identify character literals
    if (**input == '\'') {
        (*input)++;
        if (**input != '\0' && *(*input + 1) == '\'') {
            token.value[0] = *(*input)++;
            token.value[1] = *(*input)++;
            token.value[2] = '\0';
            token.type = TOKEN_CHAR;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
        return token;
    }

    // Identify string literals
    if (**input == '\"') {
        int length = 0;
        (*input)++;
        while (**input != '\"' && **input != '\0') {
            token.value[length++] = *(*input)++;
        }
        if (**input == '\"') {
            (*input)++;
            token.value[length] = '\0';
            token.type = TOKEN_STRING;
        } else {
            token.type = TOKEN_UNKNOWN;
        }
        return token;
    }

    return token;
}