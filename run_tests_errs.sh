#!/bin/bash

max_cores=$(nproc)
N="1000000"
V="20"

for cores in $(seq 1 $max_cores); do
    echo "--- Ejecutando con $cores cores de $max_cores ---"
    
    ./bin/mainPq $N $V priority_queue $cores
    ./bin/mainMq $N 2 $V multiqueue_t2 $cores
    ./bin/mainMq $N 4 $V multiqueue_t4 $cores
    ./bin/mainSl $N $V skiplist $cores
done