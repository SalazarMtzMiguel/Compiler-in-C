#include "../include/lexer.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char *keywords[] = {"int", "char", "if", "else", "while", "for", "return", "void","print"};
const char *operators[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "="};
const char *symbols[] = {"{", "}", "(", ")", "[", "]", ";", ","};

int is_keyword(const char *str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_operator(const char *str) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(str, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_symbol(const char *str) {
    for (int i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {
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
        token.value[0] = *(*input)++;
        token.value[1] = *(*input)++;
        token.value[2] = *(*input)++;
        token.value[3] = '\0';
        token.type = TOKEN_CHAR;
    } else if (**input == '\"') {
        int length = 0;
        token.value[length++] = *(*input)++;
        while (**input != '\"') {
            token.value[length++] = *(*input)++;
        }
        token.value[length++] = *(*input)++;
        token.value[length] = '\0';
        token.type = TOKEN_STRING;
    } else {
        char op[3] = {0};
        op[0] = *(*input)++;
        if (is_operator(op)) {
            token.type = TOKEN_OPERATOR;
            strcpy(token.value, op);
        } else if (is_symbol(op)) {
            token.type = TOKEN_SYMBOL;
            strcpy(token.value, op);
        } else {
            token.type = TOKEN_UNKNOWN;
            strcpy(token.value, op);
        }
    }

    return token;
}