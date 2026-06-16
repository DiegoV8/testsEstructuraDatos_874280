#!/bin/bash

max_cores=$(nproc)
V="20"

# Definimos los tamaños: de 50.000 a 5.000.000 de 50.000 en 50.000
# (Si realmente solo querías hasta 1M, cambia el 5000000 por 1000000)
for N in $(seq 50000 50000 5000000); do
    echo "=================================================="
    echo " Ejecutando pruebas para N = $N"
    echo "=================================================="

    # Cada combinación de hilos (1 y max_cores)
    for cores in 1 $max_cores; do
        
        # Bucle para repetir cada test 5 veces
        for i in {1..5}; do
            
            # ---------- Priority Queue ----------
            ./bin/mainPq $N $V priority_queue $cores
            
            # ---------- Multiqueue ----------
            ./bin/mainMq $N 2 $V multiqueue_t2 $cores
            ./bin/mainMq $N 4 $V multiqueue_t4 $cores
            
            # ---------- SkipList ----------
            ./bin/mainSl $N $V skiplist $cores
            
        done
    done
done