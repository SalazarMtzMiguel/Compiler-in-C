// semantic.c

#include "../include/semantic.h"
#include <parser.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

FILE *semantic_output_file;

// Inicializa la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
void init_symbol_table(SymbolTable *table) {
    table->count = 0;
    semantic_output_file = fopen("semantic_output.txt", "w");
    if (!semantic_output_file) {
        perror("Error al abrir el archivo");
        exit(1);
    }
}

// Agrega un simbolo a la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
// - name: nombre del simbolo
// - type: tipo del token
// Retorna: 1 si el simbolo se agrega correctamente, 0 si la tabla esta llena
int add_symbol(SymbolTable *table, const char *name, TokenType type) {
    if (table->count < 100) {
        strcpy(table->symbols[table->count].name, name);
        table->symbols[table->count].type = type;
        table->count++;
        fprintf(semantic_output_file, "Simbolo agregado: %s, Tipo: %d\n", name, type);
        return 1;
    } else {
        fprintf(stderr, "Error: La tabla de simbolos esta llena\n");
        return 0;
    }
}

// Obtiene el tipo de un simbolo en la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
// - name: nombre del simbolo
// Retorna: el tipo del token si se encuentra, TOKEN_UNKNOWN si no se encuentra
TokenType get_symbol_type(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].type;
        }
    }
    return TOKEN_UNKNOWN;
}

// Cierra el archivo de salida semantica
void close_symbol_table() {
    if (semantic_output_file) {
        fclose(semantic_output_file);
    }
}