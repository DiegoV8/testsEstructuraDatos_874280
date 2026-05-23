#!/bin/bash
max_cores=$(nproc)

./bin/mainSl 100000 20 skiplist 1
./bin/mainSl 100000 20 skiplist $max_cores