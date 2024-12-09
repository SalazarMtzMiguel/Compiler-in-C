// address_table.c
#include "address_table.h"
#include <string.h>
#include <stdio.h>

// Inicializa la tabla de direcciones, estableciendo el contador de entradas a 0
void init_address_table(AddressTable *table) {
    table->count = 0;
}

// Agrega una nueva direccion a la tabla de direcciones
// Retorna 1 si la direccion se agrega correctamente, 0 si la tabla esta llena
int add_address(AddressTable *table, const char *name, int address) {
    if (table->count < 100) {
        strcpy(table->entries[table->count].name, name);
        table->entries[table->count].address = address;
        table->count++;
        return 1;
    } else {
        fprintf(stderr, "Error: La tabla de direcciones esta llena\n");
        return 0;
    }
}

// Obtiene la direccion asociada a un nombre en la tabla de direcciones
// Retorna la direccion si se encuentra, -1 si no se encuentra
int get_address(const AddressTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].name, name) == 0) {
            return table->entries[i].address;
        }
    }
    return -1; // Direccion no encontrada
}