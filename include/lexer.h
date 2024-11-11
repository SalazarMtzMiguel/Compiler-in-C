//
// Created by Mikec on 28/10/2024.
//

#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_KEYWORD,      //#1
    TOKEN_IDENTIFIER,   //#2
    TOKEN_NUMBER,       //#3
    TOKEN_CHAR,         //#4
    TOKEN_STRING,       //#5
    TOKEN_OPERATOR,     //#6
    TOKEN_SYMBOL,       //#7
    TOKEN_UNKNOWN       //#8
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token get_next_token(const char **input);


#endif //LEXER_H
