// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Inicializa el logger abriendo el archivo de log
// Parametros:
// - filename: el nombre del archivo de log
void init_logger(const char *filename);

// Registra un mensaje en el archivo de log
// Parametros:
// - format: la cadena de formato del mensaje
// - ...: los argumentos del mensaje
void log_message(const char *format, ...);

// Cierra el archivo de log
void close_logger();

#endif // LOGGER_H