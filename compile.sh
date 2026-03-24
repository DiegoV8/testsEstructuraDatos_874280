#!/bin/bash

CXX=g++
CXXFLAGS="-Wall -Wextra -std=c++17"
OUTPUT="main"

SOURCES=$(ls src/*.cpp 2>/dev/null)

if [ -z "$SOURCES" ]; then
    echo "Error: No se encontraron archivos .cpp en el directorio."
    exit 1
fi

echo "Compilando: $SOURCES ..."
$CXX $CXXFLAGS $SOURCES -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "Compilación completada con éxito. Ejecutable creado: $OUTPUT"
else
    echo "Error durante la compilación."
    exit 1
fi