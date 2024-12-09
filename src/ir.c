// ir.c
#include "ir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crea un nuevo nodo IR
// Parametros:
// - type: el tipo de nodo IR
// - op1: el primer operando
// - op2: el segundo operando
// - result: el resultado de la operacion
// Retorna: un puntero al nuevo nodo IR
IRNode* create_ir_node(IRType type, const char *op1, const char *op2, const char *result) {
    IRNode *node = (IRNode*)malloc(sizeof(IRNode));
    strncpy(node->op1, op1, MAX_TOKEN_LENGTH);
    strncpy(node->op2, op2, MAX_TOKEN_LENGTH);
    strncpy(node->result, result, MAX_TOKEN_LENGTH);
    node->type = type;
    node->next = NULL;
    return node;
}

// Libera la memoria de una lista de nodos IR
// Parametros:
// - node: puntero al primer nodo de la lista
void free_ir_node(IRNode *node) {
    while (node) {
        IRNode *temp = node;
        node = node->next;
        free(temp);
    }
}

// Ejecuta una lista de nodos IR
// Parametros:
// - ir_list: puntero a la lista de nodos IR
void execute_ir(IRNode *ir_list) {
    IRNode *current = ir_list;
    while (current) {
        switch (current->type) {
            case IR_ADD:
                printf("%s = %s + %s\n", current->result, current->op1, current->op2);
                break;
            case IR_SUB:
                printf("%s = %s - %s\n", current->result, current->op1, current->op2);
                break;
            case IR_MUL:
                printf("%s = %s * %s\n", current->result, current->op1, current->op2);
                break;
            case IR_DIV:
                printf("%s = %s / %s\n", current->result, current->op1, current->op2);
                break;
            case IR_ASSIGN:
                printf("%s = %s\n", current->result, current->op1);
                break;
            case IR_CALL:
                if (strcmp(current->op1, "print") == 0) {
                    printf("%s\n", current->result);
                } else {
                    printf("Llamar a %s\n", current->op1);
                }
                break;
            default:
                fprintf(stderr, "Error: Tipo de nodo IR no reconocido %d\n", current->type);
                break;
        }
        current = current->next;
    }
}