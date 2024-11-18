//
// Created by Mikec on 28/10/2024.
//

#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_KEYWORD,      //#0
    TOKEN_IDENTIFIER,   //#1
    TOKEN_NUMBER,       //#2
    TOKEN_CHAR,         //#3
    TOKEN_STRING,       //#4
    TOKEN_OPERATOR,     //#5
    TOKEN_SYMBOL,       //#6
    TOKEN_UNKNOWN       //#7
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token get_next_token(const char **input);


#endif //LEXER_H
