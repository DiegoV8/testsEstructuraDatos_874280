#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include <mutex>
#include <optional>
#include "benchmark.hpp"

// Adaptador para la Priorityqueue.
template <typename T>
class HeapAdapter {
private:
    std::priority_queue<T> pq;
    mutable std::mutex mtx;

public:
    using value_type = T;

    void push(T val) { 
        std::lock_guard<std::mutex> lock(mtx);
        pq.push(val); 
    }

    void pop() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!pq.empty()) {
            pq.pop();
        }
    }

    T top() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!pq.empty()) {
            return pq.top();
        }
        return T(); 
    }

    bool empty() const { 
        std::lock_guard<std::mutex> lock(mtx);
        return pq.empty(); 
    }

    std::optional<T> try_pop() {
        std::lock_guard<std::mutex> lock(mtx); 
        
        if (!pq.empty()) {
            auto val = pq.top();
            pq.pop();
            return val;
        }
        return std::nullopt;
    }
};

int main(int argc, char *argv[]) {

    if (argc != 5) {
        std::cout << "Numero incorrecto de parametros." << std::endl;
        return 1;
    }

    const int N = atoi(argv[1]);
    const int VISUALIZAR = atoi(argv[2]);
    const std::string name = argv[3];
    const int THREADS = atoi(argv[4]);

    const std::string output = "results_/results.csv";

    HeapAdapter<int> heapTest;
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}