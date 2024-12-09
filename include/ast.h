//
// Created by Mikec on 07/12/2024.
//
// ast.h
#ifndef AST_H
#define AST_H

#include "lexer.h"

// Enumeracion que representa los diferentes tipos de nodos AST
typedef enum {
    AST_PROGRAM,               // Nodo para el programa completo
    AST_STATEMENT,             // Nodo para una declaracion
    AST_EXPRESSION,            // Nodo para una expresion
    AST_VARIABLE_DECLARATION,  // Nodo para una declaracion de variable
    AST_FUNCTION_CALL,         // Nodo para una llamada a funcion
    AST_BINARY_OPERATION,      // Nodo para una operacion binaria
    AST_LITERAL,               // Nodo para un literal
    AST_BLOCK,                 // Nodo para un bloque de codigo
    AST_ASSIGNMENT,            // Nodo para una asignacion
    AST_IF_GOTO,               // Nodo para una instruccion if-goto
    AST_RETURN,                // Nodo para una instruccion return
    AST_LABEL,                 // Nodo para una etiqueta
    AST_GOTO                   // Nodo para una instruccion goto
} ASTNodeType;

// Estructura que representa un nodo en el AST
typedef struct ASTNode {
    ASTNodeType type;          // Tipo de nodo AST
    struct ASTNode *left;      // Puntero al nodo hijo izquierdo
    struct ASTNode *right;     // Puntero al nodo hijo derecho
    Token token;               // Token asociado con el nodo
} ASTNode;

// Crea un nuevo nodo AST
// Parametros:
// - type: el tipo de nodo AST
// - token: el token asociado con el nodo
// Retorna: un puntero al nuevo nodo AST
ASTNode* create_ast_node(ASTNodeType type, Token token);

// Libera la memoria de un nodo AST y sus hijos recursivamente
// Parametros:
// - node: puntero al nodo AST a liberar
void free_ast_node(ASTNode *node);

#endif // AST_H