#include <address_table.h>
#include <asm.h>
#include <codegen.h>
#include <ir.h>
#include <logger.h>
#include <parser.h>
#include <stdio.h>
#include <stdlib.h>
// src/main.c
int main(int argc, char *argv[]) {
    // Verifica que se haya proporcionado un archivo de entrada
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <archivo.cstm>\n", argv[0]);
        return 1;
    }

    // Inicializa el logger para registrar el proceso de compilacion
    init_logger("compiler_log.txt");
    log_message("Iniciando el proceso de compilacion");

    // Abre el archivo de entrada
    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Lee el contenido del archivo de entrada
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = malloc(file_size + 1);
    if (!input) {
        perror("Error al asignar memoria");
        fclose(file);
        return 1;
    }

    fread(input, 1, file_size, file);
    input[file_size] = '\0';
    fclose(file);

    // Inicializa el parser y parsea el programa
    Parser parser;
    init_parser(&parser, input);
    ASTNode *program = parse_program(&parser);

    // Inicializa la tabla de direcciones
    AddressTable address_table;
    init_address_table(&address_table);

    // Genera el codigo intermedio (IR)
    IRNode *ir_list = NULL;
    generate_ir(program, &ir_list, &address_table);

    // Genera el codigo ensamblador
    AsmInstruction *asm_list = NULL;
    generate_asm(ir_list, &asm_list);

    // Imprime el codigo ensamblador
    AsmInstruction *current = asm_list;
    while (current) {
        printf("%s\n", current->instruction);
        log_message("Instruccion de ensamblador generada: %s", current->instruction);
        current = current->next;
    }

    // Libera la memoria del AST
    free_ast_node(program);

    // Libera la memoria del IR
    free_ir_node(ir_list);

    // Libera la memoria del codigo ensamblador
    free_asm_instruction(asm_list);

    // Libera la memoria del input
    free(input);

    // Finaliza el logger
    log_message("Proceso de compilacion finalizado");
    close_logger();
    return 0;
}