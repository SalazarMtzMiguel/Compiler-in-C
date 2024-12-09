// src/asm.c
#include "asm.h"
#include "ir.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Crea una nueva instruccion de ensamblador
// Parametros:
// - instruction: la instruccion de ensamblador como cadena de caracteres
// Retorna: un puntero a la nueva instruccion de ensamblador
AsmInstruction* create_asm_instruction(const char *instruction) {
    AsmInstruction *instr = (AsmInstruction*)malloc(sizeof(AsmInstruction));
    strncpy(instr->instruction, instruction, 100);
    instr->next = NULL;
    return instr;
}

// Libera la memoria de una lista de instrucciones de ensamblador
// Parametros:
// - instruction: puntero a la primera instruccion de la lista
void free_asm_instruction(AsmInstruction *instruction) {
    while (instruction) {
        AsmInstruction *temp = instruction;
        instruction = instruction->next;
        free(temp);
    }
}

// Genera el codigo ensamblador a partir de una lista de nodos IR
// Parametros:
// - ir_list: puntero a la lista de nodos IR
// - asm_list: puntero a la lista de instrucciones de ensamblador
void generate_asm(IRNode *ir_list, AsmInstruction **asm_list) {
    IRNode *current = ir_list;
    while (current) {
        char asm_instr[100];
        switch (current->type) {
            case IR_ADD:
                snprintf(asm_instr, 100, "ADD %s, %s, %s", current->result, current->op1, current->op2);
                break;
            case IR_SUB:
                snprintf(asm_instr, 100, "SUB %s, %s, %s", current->result, current->op1, current->op2);
                break;
            case IR_MUL:
                snprintf(asm_instr, 100, "MUL %s, %s, %s", current->result, current->op1, current->op2);
                break;
            case IR_DIV:
                snprintf(asm_instr, 100, "DIV %s, %s, %s", current->result, current->op1, current->op2);
                break;
            case IR_ASSIGN:
                snprintf(asm_instr, 100, "MOV %s, %s", current->result, current->op1);
                break;
            case IR_LABEL:
                snprintf(asm_instr, 100, "%s:", current->result);
                break;
            case IR_GOTO:
                snprintf(asm_instr, 100, "JMP %s", current->result);
                break;
            case IR_IF_GOTO:
                snprintf(asm_instr, 100, "JNZ %s, %s", current->op1, current->result);
                break;
            case IR_RETURN:
                snprintf(asm_instr, 100, "RET %s", current->op1);
                break;
            case IR_CALL:
                if (strcmp(current->op1, "print") == 0) {
                    snprintf(asm_instr, 100, "PRINT %s", current->result);
                } else {
                    snprintf(asm_instr, 100, "CALL %s", current->op1);
                }
                break;
            case IR_PARAM:
                snprintf(asm_instr, 100, "PUSH %s", current->op1);
                break;
            default:
                fprintf(stderr, "Error: Tipo de nodo IR no reconocido %d\n", current->type);
                return;
        }
        log_message("Instruccion de ensamblador generada: %s", asm_instr);
        AsmInstruction *instr = create_asm_instruction(asm_instr);
        instr->next = *asm_list;
        *asm_list = instr;
        current = current->next;
    }
}