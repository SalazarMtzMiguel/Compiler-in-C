//
// Created by Mikec on 28/10/2024.
//

#include "../include/semantic.h"
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