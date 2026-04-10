#!/bin/bash

CXX=g++
# Dejamos CXXFLAGS solo para opciones de compilación
CXXFLAGS="-Wall -Wextra -std=c++17 -O3"
# Creamos LDFLAGS para las librerías
LDFLAGS="-ltbb" 

# Si quieres usar el thread sanitizer en el futuro, descomenta estas dos:
# CXXFLAGS="-Wall -Wextra -std=c++17 -O3 -fsanitize=thread -g"
# LDFLAGS="-ltbb -fsanitize=thread"

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
        # ¡AQUÍ ESTÁ LA CLAVE! $LDFLAGS va al final del todo
        $CXX $CXXFLAGS "$src" src/timer.cpp -o "$BIN_DIR/$output_name" $LDFLAGS
    } 2>> $LOG_ERR
    
    if [ $? -eq 0 ]; then
        echo "[OK]"
    else
        echo "[FALLÓ] -> Ver $LOG_ERR"
    fi
done

echo "---------------------------------"
echo "Proceso terminado."