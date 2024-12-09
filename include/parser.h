//
// Created by Mikec on 28/10/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

// Estructura que representa el parser
typedef struct {
    Token current_token;  // Token actual
    const char *input;    // Cadena de entrada
} Parser;

// Inicializa el parser con la entrada proporcionada
// Parametros:
// - parser: puntero al parser
// - input: cadena de entrada
void init_parser(Parser *parser, const char *input);

// Avanza al siguiente token en la entrada
// Parametros:
// - parser: puntero al parser
void advance(Parser *parser);

// Verifica que el token actual sea del tipo esperado y avanza
// Parametros:
// - parser: puntero al parser
// - type: tipo de token esperado
void expect(Parser *parser, TokenType type);

// Parsea el programa completo
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST del programa
ASTNode* parse_program(Parser *parser);

// Parsea una declaracion
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST de la declaracion
ASTNode* parse_statement(Parser *parser);

// Parsea una expresion
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST de la expresion
ASTNode* parse_expression(Parser *parser);

// Parsea un bloque de codigo
// Parametros:
// - parser: puntero al parser
// Retorna: un puntero al nodo AST del bloque
ASTNode* parse_block(Parser *parser);

#endif // PARSER_H