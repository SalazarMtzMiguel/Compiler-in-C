// codegen.c
#include "codegen.h"
#include "ir.h"
#include "ast.h"
#include "address_table.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

static int temp_var_count = 0;

// Genera el codigo intermedio (IR) a partir de un nodo AST
// Parametros:
// - node: puntero al nodo AST
// - ir_list: puntero a la lista de nodos IR
// - address_table: puntero a la tabla de direcciones
void generate_ir(ASTNode *node, IRNode **ir_list, AddressTable *address_table) {
    if (!node) return;

    switch (node->type) {
        case AST_PROGRAM:
            log_message("Generando IR para el programa");
            generate_ir(node->left, ir_list, address_table);
            generate_ir(node->right, ir_list, address_table);
            break;
        case AST_STATEMENT:
            log_message("Generando IR para la declaracion");
            generate_ir(node->left, ir_list, address_table);
            generate_ir(node->right, ir_list, address_table);
            break;
        case AST_EXPRESSION:
            log_message("Generando IR para la expresion");
            if (node->left && node->right) {
                char temp[MAX_TOKEN_LENGTH];
                snprintf(temp, MAX_TOKEN_LENGTH, "t%d", temp_var_count++);
                IRType ir_type;
                if (strcmp(node->token.value, "+") == 0) {
                    ir_type = IR_ADD;
                } else if (strcmp(node->token.value, "-") == 0) {
                    ir_type = IR_SUB;
                } else if (strcmp(node->token.value, "*") == 0) {
                    ir_type = IR_MUL;
                } else if (strcmp(node->token.value, "/") == 0) {
                    ir_type = IR_DIV;
                } else {
                    fprintf(stderr, "Error: Operador no reconocido %s\n", node->token.value);
                    return;
                }
                IRNode *ir_node = create_ir_node(ir_type, node->left->token.value, node->right->token.value, temp);
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: %s = %s %s %s", temp, node->left->token.value, node->token.value, node->right->token.value);
            }
            break;
        case AST_VARIABLE_DECLARATION:
            log_message("Generando IR para la declaracion de variable");
            if (node->left) {
                IRNode *ir_node = create_ir_node(IR_ASSIGN, node->left->token.value, "", node->token.value);
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: %s = %s", node->token.value, node->left->token.value);
            }
            break;
        case AST_ASSIGNMENT:
            log_message("Generando IR para la asignacion");
            if (node->left && node->right) {
                IRNode *ir_node = create_ir_node(IR_ASSIGN, node->right->token.value, "", node->left->token.value);
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: %s = %s", node->left->token.value, node->right->token.value);
            }
            break;
        case AST_FUNCTION_CALL:
            log_message("Generando IR para la llamada a funcion");
            if (strcmp(node->token.value, "print") == 0) {
                IRNode *ir_node = create_ir_node(IR_CALL, "print", "", node->left->token.value);
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: print %s", node->left->token.value);
            } else {
                int address = get_address(address_table, node->token.value);
                if (address == -1) {
                    fprintf(stderr, "Error: Funcion %s no encontrada\n", node->token.value);
                    return;
                }
                char address_str[MAX_TOKEN_LENGTH];
                snprintf(address_str, MAX_TOKEN_LENGTH, "%d", address);
                IRNode *ir_node = create_ir_node(IR_CALL, address_str, "", "");
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: call %s", node->token.value);
            }
            break;
        case AST_LITERAL:
            // No se necesita generar IR para literales directamente
            break;
        case AST_LABEL:
            log_message("Generando IR para la etiqueta");
            {
                IRNode *ir_node = create_ir_node(IR_LABEL, node->token.value, "", "");
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: label %s", node->token.value);
            }
            break;
        case AST_GOTO:
            log_message("Generando IR para goto");
            {
                IRNode *ir_node = create_ir_node(IR_GOTO, node->token.value, "", "");
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: goto %s", node->token.value);
            }
            break;
        case AST_IF_GOTO:
            log_message("Generando IR para if-goto");
            {
                IRNode *ir_node = create_ir_node(IR_IF_GOTO, node->left->token.value, "", node->right->token.value);
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: if %s goto %s", node->left->token.value, node->right->token.value);
            }
            break;
        case AST_RETURN:
            log_message("Generando IR para return");
            {
                IRNode *ir_node = create_ir_node(IR_RETURN, node->token.value, "", "");
                ir_node->next = *ir_list;
                *ir_list = ir_node;
                log_message("Nodo IR generado: return %s", node->token.value);
            }
            break;
        default:
            fprintf(stderr, "Error: Tipo de nodo AST no reconocido %d\n", node->type);
            break;
    }
}