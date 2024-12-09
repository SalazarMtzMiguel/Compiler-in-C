// ir.h
#ifndef IR_H
#define IR_H

#include "lexer.h"

// Enumeracion que representa los diferentes tipos de nodos IR
typedef enum {
    IR_ADD,       // Nodo para una operacion de suma
    IR_SUB,       // Nodo para una operacion de resta
    IR_MUL,       // Nodo para una operacion de multiplicacion
    IR_DIV,       // Nodo para una operacion de division
    IR_ASSIGN,    // Nodo para una asignacion
    IR_LABEL,     // Nodo para una etiqueta
    IR_GOTO,      // Nodo para una instruccion goto
    IR_IF_GOTO,   // Nodo para una instruccion if-goto
    IR_RETURN,    // Nodo para una instruccion return
    IR_CALL,      // Nodo para una llamada a funcion
    IR_PARAM,     // Nodo para un parametro de funcion
} IRType;

// Estructura que representa un nodo en el IR
typedef struct IRNode {
    IRType type;                  // Tipo de nodo IR
    char op1[MAX_TOKEN_LENGTH];   // Primer operando
    char op2[MAX_TOKEN_LENGTH];   // Segundo operando
    char result[MAX_TOKEN_LENGTH];// Resultado de la operacion
    struct IRNode *next;          // Puntero al siguiente nodo en la lista
} IRNode;

// Crea un nuevo nodo IR
// Parametros:
// - type: el tipo de nodo IR
// - op1: el primer operando
// - op2: el segundo operando
// - result: el resultado de la operacion
// Retorna: un puntero al nuevo nodo IR
IRNode* create_ir_node(IRType type, const char *op1, const char *op2, const char *result);

// Libera la memoria de una lista de nodos IR
// Parametros:
// - node: puntero al primer nodo de la lista
void free_ir_node(IRNode *node);

// Ejecuta una lista de nodos IR
// Parametros:
// - ir_list: puntero a la lista de nodos IR
void execute_ir(IRNode *ir_list);

#endif // IR_H