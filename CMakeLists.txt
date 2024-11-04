cmake_minimum_required(VERSION 3.29)
project(Compiler C)

set(CMAKE_C_STANDARD 11)

add_executable(Compiler
        src/main.c
        src/lexer.c
        include/lexer.h
        src/parser.c
        include/parser.h
        src/semantic.c
        include/semantic.h
        src/codegen.c
        include/codegen.h
        src/utils.c
        include/utils.h
)
