#!/bin/bash
max_cores=$(nproc)

./bin/mainSl 1000000 20 skiplist 1
./bin/mainSl 1000000 20 skiplist $max_cores