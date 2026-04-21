#!/bin/bash

max_cores=$(nproc)

# ---------- Priority Queue ----------

./bin/mainPq 10000 20 priority_queue 1
./bin/mainPq 10000 20 priority_queue 1
./bin/mainPq 10000 20 priority_queue 1
./bin/mainPq 10000 20 priority_queue 1
./bin/mainPq 10000 20 priority_queue 1

./bin/mainPq 10000 20 priority_queue $max_cores
./bin/mainPq 10000 20 priority_queue $max_cores
./bin/mainPq 10000 20 priority_queue $max_cores
./bin/mainPq 10000 20 priority_queue $max_cores
./bin/mainPq 10000 20 priority_queue $max_cores

./bin/mainPq 100000 20 priority_queue 1
./bin/mainPq 100000 20 priority_queue 1
./bin/mainPq 100000 20 priority_queue 1
./bin/mainPq 100000 20 priority_queue 1
./bin/mainPq 100000 20 priority_queue 1

./bin/mainPq 100000 20 priority_queue $max_cores
./bin/mainPq 100000 20 priority_queue $max_cores
./bin/mainPq 100000 20 priority_queue $max_cores
./bin/mainPq 100000 20 priority_queue $max_cores
./bin/mainPq 100000 20 priority_queue $max_cores

./bin/mainPq 1000000 20 priority_queue 1
./bin/mainPq 1000000 20 priority_queue 1
./bin/mainPq 1000000 20 priority_queue 1
./bin/mainPq 1000000 20 priority_queue 1
./bin/mainPq 1000000 20 priority_queue 1

./bin/mainPq 1000000 20 priority_queue $max_cores
./bin/mainPq 1000000 20 priority_queue $max_cores
./bin/mainPq 1000000 20 priority_queue $max_cores
./bin/mainPq 1000000 20 priority_queue $max_cores
./bin/mainPq 1000000 20 priority_queue $max_cores

./bin/mainPq 5000000 20 priority_queue 1
./bin/mainPq 5000000 20 priority_queue 1
./bin/mainPq 5000000 20 priority_queue 1
./bin/mainPq 5000000 20 priority_queue 1
./bin/mainPq 5000000 20 priority_queue 1

./bin/mainPq 5000000 20 priority_queue $max_cores
./bin/mainPq 5000000 20 priority_queue $max_cores
./bin/mainPq 5000000 20 priority_queue $max_cores
./bin/mainPq 5000000 20 priority_queue $max_cores
./bin/mainPq 5000000 20 priority_queue $max_cores

# ---------- Multiqueue ----------

./bin/mainMq 10000 2 20 multiqueue_t2 1
./bin/mainMq 10000 2 20 multiqueue_t2 1
./bin/mainMq 10000 2 20 multiqueue_t2 1
./bin/mainMq 10000 2 20 multiqueue_t2 1
./bin/mainMq 10000 2 20 multiqueue_t2 1

./bin/mainMq 10000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 10000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 10000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 10000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 10000 2 20 multiqueue_t2 $max_cores

./bin/mainMq 10000 4 20 multiqueue_t4 1
./bin/mainMq 10000 4 20 multiqueue_t4 1
./bin/mainMq 10000 4 20 multiqueue_t4 1
./bin/mainMq 10000 4 20 multiqueue_t4 1
./bin/mainMq 10000 4 20 multiqueue_t4 1

./bin/mainMq 10000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 10000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 10000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 10000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 10000 4 20 multiqueue_t4 $max_cores

./bin/mainMq 100000 2 20 multiqueue_t2 1
./bin/mainMq 100000 2 20 multiqueue_t2 1
./bin/mainMq 100000 2 20 multiqueue_t2 1
./bin/mainMq 100000 2 20 multiqueue_t2 1
./bin/mainMq 100000 2 20 multiqueue_t2 1

./bin/mainMq 100000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 100000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 100000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 100000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 100000 2 20 multiqueue_t2 $max_cores

./bin/mainMq 100000 4 20 multiqueue_t4 1
./bin/mainMq 100000 4 20 multiqueue_t4 1
./bin/mainMq 100000 4 20 multiqueue_t4 1
./bin/mainMq 100000 4 20 multiqueue_t4 1
./bin/mainMq 100000 4 20 multiqueue_t4 1

./bin/mainMq 100000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 100000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 100000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 100000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 100000 4 20 multiqueue_t4 $max_cores

./bin/mainMq 1000000 2 20 multiqueue_t2 1
./bin/mainMq 1000000 2 20 multiqueue_t2 1
./bin/mainMq 1000000 2 20 multiqueue_t2 1
./bin/mainMq 1000000 2 20 multiqueue_t2 1
./bin/mainMq 1000000 2 20 multiqueue_t2 1

./bin/mainMq 1000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 1000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 1000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 1000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 1000000 2 20 multiqueue_t2 $max_cores

./bin/mainMq 1000000 4 20 multiqueue_t4 1
./bin/mainMq 1000000 4 20 multiqueue_t4 1
./bin/mainMq 1000000 4 20 multiqueue_t4 1
./bin/mainMq 1000000 4 20 multiqueue_t4 1
./bin/mainMq 1000000 4 20 multiqueue_t4 1

./bin/mainMq 1000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 1000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 1000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 1000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 1000000 4 20 multiqueue_t4 $max_cores

./bin/mainMq 5000000 2 20 multiqueue_t2 1
./bin/mainMq 5000000 2 20 multiqueue_t2 1
./bin/mainMq 5000000 2 20 multiqueue_t2 1
./bin/mainMq 5000000 2 20 multiqueue_t2 1
./bin/mainMq 5000000 2 20 multiqueue_t2 1

./bin/mainMq 5000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 5000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 5000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 5000000 2 20 multiqueue_t2 $max_cores
./bin/mainMq 5000000 2 20 multiqueue_t2 $max_cores

./bin/mainMq 5000000 4 20 multiqueue_t4 1
./bin/mainMq 5000000 4 20 multiqueue_t4 1
./bin/mainMq 5000000 4 20 multiqueue_t4 1
./bin/mainMq 5000000 4 20 multiqueue_t4 1
./bin/mainMq 5000000 4 20 multiqueue_t4 1

./bin/mainMq 5000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 5000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 5000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 5000000 4 20 multiqueue_t4 $max_cores
./bin/mainMq 5000000 4 20 multiqueue_t4 $max_cores

# ---------- SkipList ----------

./bin/mainSl 10000 20 skiplist 1
./bin/mainSl 10000 20 skiplist 1
./bin/mainSl 10000 20 skiplist 1
./bin/mainSl 10000 20 skiplist 1
./bin/mainSl 10000 20 skiplist 1

./bin/mainSl 10000 20 skiplist $max_cores
./bin/mainSl 10000 20 skiplist $max_cores
./bin/mainSl 10000 20 skiplist $max_cores
./bin/mainSl 10000 20 skiplist $max_cores
./bin/mainSl 10000 20 skiplist $max_cores

./bin/mainSl 100000 20 skiplist 1
./bin/mainSl 100000 20 skiplist 1
./bin/mainSl 100000 20 skiplist 1
./bin/mainSl 100000 20 skiplist 1
./bin/mainSl 100000 20 skiplist 1

./bin/mainSl 100000 20 skiplist $max_cores
./bin/mainSl 100000 20 skiplist $max_cores
./bin/mainSl 100000 20 skiplist $max_cores
./bin/mainSl 100000 20 skiplist $max_cores
./bin/mainSl 100000 20 skiplist $max_cores

./bin/mainSl 1000000 20 skiplist 1
./bin/mainSl 1000000 20 skiplist 1
./bin/mainSl 1000000 20 skiplist 1
./bin/mainSl 1000000 20 skiplist 1
./bin/mainSl 1000000 20 skiplist 1

./bin/mainSl 1000000 20 skiplist $max_cores
./bin/mainSl 1000000 20 skiplist $max_cores
./bin/mainSl 1000000 20 skiplist $max_cores
./bin/mainSl 1000000 20 skiplist $max_cores
./bin/mainSl 1000000 20 skiplist $max_cores

./bin/mainSl 5000000 20 skiplist 1
./bin/mainSl 5000000 20 skiplist 1
./bin/mainSl 5000000 20 skiplist 1
./bin/mainSl 5000000 20 skiplist 1
./bin/mainSl 5000000 20 skiplist 1

./bin/mainSl 5000000 20 skiplist $max_cores
./bin/mainSl 5000000 20 skiplist $max_cores
./bin/mainSl 5000000 20 skiplist $max_cores
./bin/mainSl 5000000 20 skiplist $max_cores
./bin/mainSl 5000000 20 skiplist $max_cores