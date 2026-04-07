#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include <mutex>
#include "benchmark.hpp"

// Adaptador para la Estructura de Datos que sea
template <typename T>
class HeapAdapter {
private:
    std::priority_queue<T> pq;
    mutable std::mutex mtx; // Mutex global para proteger la cola entera

public:
    using value_type = T;

    void push(T val) { 
        std::lock_guard<std::mutex> lock(mtx); // Bloqueamos antes de insertar
        pq.push(val); 
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mtx); // Bloqueamos antes de borrar
        if (!pq.empty()) {
            pq.pop();
        }
    }

    T top() {
        std::lock_guard<std::mutex> lock(mtx); // Bloqueamos antes de leer
        if (!pq.empty()) {
            return pq.top();
        }
        return T(); 
    }

    bool empty() const { 
        std::lock_guard<std::mutex> lock(mtx); // Bloqueamos antes de comprobar
        return pq.empty(); 
    }
};

int main() {
    const int N = 10000;
    const int VISUALIZAR = 20;
    const std::string output = "../results_/results_ext.csv";
    const std::string name = "priority_queue";
    //const int THREADS = 1;
    const int THREADS = std::thread::hardware_concurrency();

    // Estructura de Datos
    HeapAdapter<int> heapTest;
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}