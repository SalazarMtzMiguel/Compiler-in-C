// codegen.h
#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "ir.h"
#include "address_table.h"

// Genera el codigo intermedio (IR) a partir de un nodo AST
// Parametros:
// - node: puntero al nodo AST
// - ir_list: puntero a la lista de nodos IR
// - address_table: puntero a la tabla de direcciones
void generate_ir(ASTNode *node, IRNode **ir_list, AddressTable *address_table);

#endif // CODEGEN_H