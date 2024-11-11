//
// Created by Mikec on 28/10/2024.
//

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "lexer.h"

typedef struct {
    char name[MAX_TOKEN_LENGTH];
    TokenType type;
} Symbol;

typedef struct {
    Symbol symbols[100];
    int count;
} SymbolTable;

void init_symbol_table(SymbolTable *table);
int add_symbol(SymbolTable *table, const char *name, TokenType type);
TokenType get_symbol_type(SymbolTable *table, const char *name);

#endif // SEMANTIC_H