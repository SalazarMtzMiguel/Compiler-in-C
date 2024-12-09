// address_table.h
#ifndef ADDRESS_TABLE_H
#define ADDRESS_TABLE_H

#include "lexer.h"

// Estructura que representa una entrada en la tabla de direcciones
typedef struct {
    char name[MAX_TOKEN_LENGTH]; // Nombre del simbolo
    int address;                 // Direccion asociada al simbolo
} AddressEntry;

// Estructura que representa la tabla de direcciones
typedef struct {
    AddressEntry entries[100]; // Arreglo de entradas de direcciones
    int count;                 // Contador de entradas en la tabla
} AddressTable;

// Inicializa la tabla de direcciones
// Parametros:
// - table: puntero a la tabla de direcciones
void init_address_table(AddressTable *table);

// Agrega una nueva direccion a la tabla de direcciones
// Parametros:
// - table: puntero a la tabla de direcciones
// - name: nombre del simbolo
// - address: direccion asociada al simbolo
// Retorna: 1 si la direccion se agrega correctamente, 0 si la tabla esta llena
int add_address(AddressTable *table, const char *name, int address);

// Obtiene la direccion asociada a un nombre en la tabla de direcciones
// Parametros:
// - table: puntero a la tabla de direcciones (const)
// - name: nombre del simbolo
// Retorna: la direccion si se encuentra, -1 si no se encuentra
int get_address(const AddressTable *table, const char *name);

#endif // ADDRESS_TABLE_H