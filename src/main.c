#include <stdio.h>
#include "../include/lexer.h"
//
// Created by Mikec on 28/10/2024.
//
#include <stdio.h>
#include "../include/lexer.h"
#include "../include/semantic.h"

int main() {
    const char *input = "int(int z){int x; x=z*x; return x;}";
    Token token;
    SymbolTable symbol_table;

    init_symbol_table(&symbol_table);

    while (*input != '\0') {
        token = get_next_token(&input);
        printf("Token: %s, Type: %d\n", token.value, token.type);

        if (token.type == TOKEN_KEYWORD || token.type == TOKEN_IDENTIFIER) {
            add_symbol(&symbol_table, token.value, token.type);
        }
    }

    // Generación de código (ejemplo simple)
    for (int i = 0; i < symbol_table.count; i++) {
        printf("Symbol: %s, Type: %d\n", symbol_table.symbols[i].name, symbol_table.symbols[i].type);
    }

    return 0;
}