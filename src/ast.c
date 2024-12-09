// ast.c
#include "ast.h"
#include <stdlib.h>

// Crea un nuevo nodo AST
// Parametros:
// - type: el tipo de nodo AST
// - token: el token asociado con el nodo
// Retorna: un puntero al nuevo nodo AST
ASTNode* create_ast_node(ASTNodeType type, Token token) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->token = token;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Libera la memoria de un nodo AST y sus hijos recursivamente
// Parametros:
// - node: puntero al nodo AST a liberar
void free_ast_node(ASTNode *node) {
    if (node) {
        free_ast_node(node->left);
        free_ast_node(node->right);
        free(node);
    }
}