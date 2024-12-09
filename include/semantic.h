//
// Created by Mikec on 28/10/2024.
//

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "lexer.h"

// Estructura que representa un simbolo en la tabla de simbolos
typedef struct {
    char name[MAX_TOKEN_LENGTH]; // Nombre del simbolo
    TokenType type;              // Tipo del token
} Symbol;

// Estructura que representa la tabla de simbolos
typedef struct {
    Symbol symbols[100]; // Arreglo de simbolos
    int count;           // Contador de simbolos en la tabla
} SymbolTable;

// Inicializa la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
void init_symbol_table(SymbolTable *table);

// Agrega un simbolo a la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
// - name: nombre del simbolo
// - type: tipo del token
// Retorna: 1 si el simbolo se agrega correctamente, 0 si la tabla esta llena
int add_symbol(SymbolTable *table, const char *name, TokenType type);

// Obtiene el tipo de un simbolo en la tabla de simbolos
// Parametros:
// - table: puntero a la tabla de simbolos
// - name: nombre del simbolo
// Retorna: el tipo del token si se encuentra, TOKEN_UNKNOWN si no se encuentra
TokenType get_symbol_type(SymbolTable *table, const char *name);

#endif // SEMANTIC_H