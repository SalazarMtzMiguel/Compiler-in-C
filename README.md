Proyecto de Compilador en C
Este proyecto es un compilador básico escrito en C, diseñado para procesar un lenguaje de programación ficticio que admite tipos de datos básicos (int, char, string), estructuras de control (if, while, for), funciones, y operaciones comunes. La compilación se gestiona usando CMake y MinGW en Windows.

Estructura del Proyecto
El proyecto está organizado en la siguiente estructura de carpetas y archivos:

project-root/
├── build/                  # Archivos de compilación generados por CMake
├── src/                    # Código fuente del compilador
│   ├── main.c              # Punto de entrada del compilador
│   ├── lexer.c             # Analizador léxico
│   ├── parser.c            # Analizador sintáctico
│   ├── semantic_analyzer.c # Analizador semántico
│   ├── codegen.c           # Generador de código
│   └── utils.c             # Funciones utilitarias
├── include/                # Archivos de cabecera
│   ├── lexer.h
│   ├── parser.h
│   ├── semantic_analyzer.h
│   ├── codegen.h
│   └── utils.h
├── tests/                  # Pruebas y archivos de entrada para el compilador
├── CMakeLists.txt          # Archivo de configuración de CMake
└── README.md               # Archivo de documentación

Compilación
Para compilar el proyecto, sigue estos pasos:

Navega al directorio del proyecto:

bash
Copiar código
cd path/to/project-root
Crea y accede al directorio de construcción:

bash
Copiar código
mkdir build
cd build
Genera los archivos de compilación usando CMake:

bash
Copiar código
cmake -G "MinGW Makefiles" ..
Compila el proyecto:



cmake --build .
Ejecución
Para ejecutar el compilador en un archivo de prueba, usa el siguiente comando:


.\compiler ..\tests\codigo.cstm
Donde codigo.cstm es un archivo en el lenguaje ficticio de este compilador.

Descripción de los Componentes
1. Lexer (Analizador Léxico)
El lexer convierte el código fuente en una serie de tokens, clasificando palabras clave, identificadores, operadores y símbolos. El código se encuentra en src/lexer.c.

2. Parser (Analizador Sintáctico)
El parser organiza los tokens en una estructura de árbol que representa la jerarquía y el flujo del programa. Implementado en src/parser.c.

3. Analizador Semántico
Verifica la validez semántica, como el uso correcto de tipos y funciones. Su código está en src/semantic_analyzer.c.

4. Generador de Código
Genera código en lenguaje ensamblador o en un lenguaje de máquina objetivo. Implementado en src/codegen.c.

5. Utils (Utilidades)
Contiene funciones auxiliares que se usan en diferentes partes del compilador. El código está en src/utils.c.

Contribuciones
Este proyecto es experimental y abierto a mejoras. Si deseas contribuir:

Haz un fork del proyecto.
Crea una rama nueva.
Envía un pull request describiendo los cambios.
