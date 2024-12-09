// lexer.c

#include "../include/lexer.h"
#include "../include/semantic.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Lista de palabras clave reconocidas
const char *keywords[] = {"int", "char", "if", "else", "while", "for", "return", "void", "print", "break", "string", "main", "fun"};

// Lista de operadores reconocidos
const char *operators[] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "="};

// Lista de simbolos reconocidos
const char *symbols[] = {"{", "}", "(", ")", "[", "]", ";", ","};

// Constantes para calcular el numero de elementos en cada lista
#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))
#define OPERATOR_COUNT (sizeof(operators) / sizeof(operators[0]))
#define SYMBOL_COUNT (sizeof(symbols) / sizeof(symbols[0]))

// Verifica si una cadena es una palabra clave
// Parametros:
// - str: la cadena a verificar
// Retorna: 1 si es una palabra clave, 0 en caso contrario
int is_keyword(const char *str) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Verifica si una cadena es un operador
// Parametros:
// - str: la cadena a verificar
// Retorna: 1 si es un operador, 0 en caso contrario
int is_operator(const char *str) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (strcmp(str, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Verifica si una cadena es un simbolo
// Parametros:
// - str: la cadena a verificar
// Retorna: 1 si es un simbolo, 0 en caso contrario
int is_symbol(const char *str) {
    for (int i = 0; i < SYMBOL_COUNT; i++) {
        if (strcmp(str, symbols[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Obtiene el siguiente token de la entrada
// Parametros:
// - input: puntero a la cadena de entrada
// Retorna: el siguiente token
Token get_next_token(const char **input) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    // Saltar espacios en blanco
    while (isspace(**input)) (*input)++;

    if (**input == '\0') {
        return token; // Fin de la entrada
    }

    // Identificar simbolos de un solo caracter
    char symbol[2] = {*(*input), '\0'};
    if (is_symbol(symbol)) {
        token.value[0] = *(*input)++;
        token.value[1] = '\0';
        token.type = TOKEN_SYMBOL;
        return token;
    }

    // Identificar operadores (uno o dos caracteres)
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

    // Identificar palabras clave o identificadores
    if (isalpha(**input) || **input == '_') {
        int length = 0;
        while (isalnum(**input) || **input == '_') {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = is_keyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    }

    // Identificar numeros
    if (isdigit(**input)) {
        int length = 0;
        while (isdigit(**input)) {
            token.value[length++] = *(*input)++;
        }
        token.value[length] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    // Identificar literales de caracteres
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

    // Identificar literales de cadenas
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

    fprintf(stderr, "Error lexico: caracter no reconocido '%c'\n", **input);
    (*input)++;
    return token;
}