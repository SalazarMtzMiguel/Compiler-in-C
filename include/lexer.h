//
// Created by Mikec on 28/10/2024.
//

#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_CHAR,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_SYMBOL,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token get_next_token(const char **input);


#endif //LEXER_H
