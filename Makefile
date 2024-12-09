# Nombre del ejecutable final
EXEC = compiler

# Directorios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Archivos fuente y archivos objeto
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)

# Regla principal para compilar el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Regla para compilar archivos .c a .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpiar archivos generados
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)