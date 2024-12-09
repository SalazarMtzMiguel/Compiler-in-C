// include/asm.h
#ifndef ASM_H
#define ASM_H
#include <ir.h>

// Estructura que representa una instruccion de ensamblador
typedef struct AsmInstruction {
    char instruction[100];       // La instruccion de ensamblador como cadena de caracteres
    struct AsmInstruction *next; // Puntero a la siguiente instruccion en la lista
} AsmInstruction;

// Crea una nueva instruccion de ensamblador
// Parametros:
// - instruction: la instruccion de ensamblador como cadena de caracteres
// Retorna: un puntero a la nueva instruccion de ensamblador
AsmInstruction* create_asm_instruction(const char *instruction);

// Libera la memoria de una lista de instrucciones de ensamblador
// Parametros:
// - instruction: puntero a la primera instruccion de la lista
void free_asm_instruction(AsmInstruction *instruction);

// Genera el codigo ensamblador a partir de una lista de nodos IR
// Parametros:
// - ir_list: puntero a la lista de nodos IR
// - asm_list: puntero a la lista de instrucciones de ensamblador
void generate_asm(IRNode *ir_list, AsmInstruction **asm_list);

#endif // ASM_H