#include <stdio.h>
#include "../include/lexer.h"
//
// Created by Mikec on 28/10/2024.
//

int main() {
    const char *input = "int main() { print(hola) return 0; }";
    Token token;

    while (*input != '\0') {
        token = get_next_token(&input);
        printf("Token: %s, Type: %d\n", token.value, token.type);
    }

    return 0;
}