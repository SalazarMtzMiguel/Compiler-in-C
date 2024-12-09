// lexer.h

#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 100

// Enumeracion que representa los diferentes tipos de tokens
typedef enum {
    TOKEN_KEYWORD,      // Token para una palabra clave
    TOKEN_IDENTIFIER,   // Token para un identificador
    TOKEN_NUMBER,       // Token para un numero
    TOKEN_CHAR,         // Token para un caracter
    TOKEN_STRING,       // Token para una cadena de caracteres
    TOKEN_OPERATOR,     // Token para un operador
    TOKEN_SYMBOL,       // Token para un simbolo
    TOKEN_UNKNOWN       // Token desconocido
} TokenType;

// Estructura que representa un token
typedef struct {
    TokenType type;                 // Tipo de token
    char value[MAX_TOKEN_LENGTH];   // Valor del token
} Token;

// Obtiene el siguiente token de la entrada
// Parametros:
// - input: puntero a la cadena de entrada
// Retorna: el siguiente token
Token get_next_token(const char **input);

#endif // LEXER_H