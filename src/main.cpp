#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include "benchmark.hpp"

// Adaptador para la Estructura de Datos que sea
template <typename T>
class HeapAdapter : public std::priority_queue<T> { // Heap
public:
    // La interfaz estándar ya tiene push, pop, top, empty.
    
    /* En caso de no tenerla:
    void push(T val) { ... }
    void pop() { ... }
    T top() { ... }
    bool empty() { ... }
    */
};

int main() {
    const int N = 100000;
    const int VISUALIZAR = 20;
    const std::string output = "results_/results.csv";
    const std::string name = "priority_queue";

    // Estructura de Datos
    HeapAdapter<int> heapTest;
    run_benchmark(heapTest, N, VISUALIZAR, name, output);

    return 0;
}