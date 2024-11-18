#include "../include/semantic.h"
#include <parser.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *semantic_output_file;

void init_symbol_table(SymbolTable *table) {
    table->count = 0;
    semantic_output_file = fopen("semantic_output.txt", "w");
    if (!semantic_output_file) {
        perror("Error opening file");
        exit(1);
    }
}

int add_symbol(SymbolTable *table, const char *name, TokenType type) {
    if (table->count < 100) {
        strcpy(table->symbols[table->count].name, name);
        table->symbols[table->count].type = type;
        table->count++;
        fprintf(semantic_output_file, "Added symbol: %s, Type: %d\n", name, type);
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