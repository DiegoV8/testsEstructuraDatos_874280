#!/bin/bash

CXX=g++
CXXFLAGS="-Wall -Wextra -std=c++17 -O3"
# CXXFLAGS="-Wall -Wextra -std=c++17 -O3 -fsanitize=thread -g"
BIN_DIR="bin"
LOG_ERR="errores.txt"

mkdir -p $BIN_DIR
> $LOG_ERR  

SOURCES=$(ls src/main*.cpp 2>/dev/null)

if [ -z "$SOURCES" ]; then
    echo "Error: No se encontraron archivos src/mainXX.cpp"
    exit 1
fi

echo "Iniciando compilación. Los errores se guardarán en $LOG_ERR"
echo "---------------------------------"

for src in $SOURCES; do
    filename=$(basename "$src")
    output_name="${filename%.cpp}"
    
    echo -n "Compilando $filename... "

    {
        $CXX $CXXFLAGS "$src" src/timer.cpp -o "$BIN_DIR/$output_name"
    } 2>> $LOG_ERR
    
    if [ $? -eq 0 ]; then
        echo "[OK]"
    else
        echo "[FALLÓ] -> Ver $LOG_ERR"
    fi
done

echo "---------------------------------"
echo "Proceso terminado."