// logger.c
#include "logger.h"
#include <stdarg.h>
#include <stdlib.h>

static FILE *log_file = NULL;

// Inicializa el logger abriendo el archivo de log
// Parametros:
// - filename: el nombre del archivo de log
void init_logger(const char *filename) {
    log_file = fopen(filename, "w");
    if (!log_file) {
        perror("Error al abrir el archivo de log");
        exit(1);
    }
}

// Registra un mensaje en el archivo de log
// Parametros:
// - format: la cadena de formato del mensaje
// - ...: los argumentos del mensaje
void log_message(const char *format, ...) {
    if (!log_file) return;

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);
    fprintf(log_file, "\n");
}

// Cierra el archivo de log
void close_logger() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}