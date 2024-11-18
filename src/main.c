//
// Created by Mikec on 28/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"

void print_tokens(const char *input, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    const char *input_ptr = input;
    Token token;
    while (*input_ptr != '\0') {
        token = get_next_token(&input_ptr);
        fprintf(file, "Token: %s, Type: %d\n", token.value, token.type);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.cstm>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = malloc(file_size + 1);
    if (!input) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(input, 1, file_size, file);
    input[file_size] = '\0';
    fclose(file);

    // Print tokens to lexer_output.txt
    print_tokens(input, "lexer_output.txt");

    // Initialize parser and parse the program
    Parser parser;
    init_parser(&parser, input);
    parse_program(&parser);

    free(input);
    return 0;
}

/*
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.cstm>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = malloc(file_size + 1);
    if (!input) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(input, 1, file_size, file);
    input[file_size] = '\0';
    fclose(file);

    Token token;
    SymbolTable symbol_table;
    init_symbol_table(&symbol_table);

    const char *input_ptr = input;
    while (*input_ptr != '\0') {
        token = get_next_token(&input_ptr);
        printf("Token: %s, Type: %d\n", token.value, token.type);

        if (token.type == TOKEN_KEYWORD || token.type == TOKEN_IDENTIFIER) {
            add_symbol(&symbol_table, token.value, token.type);
        }
    }

    // Generación de código (ejemplo simple)
    for (int i = 0; i < symbol_table.count; i++) {
        printf("Symbol: %s, Type: %d\n", symbol_table.symbols[i].name, symbol_table.symbols[i].type);
    }

    free(input);
    return 0;
}*/