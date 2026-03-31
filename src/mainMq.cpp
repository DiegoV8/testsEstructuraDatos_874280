#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include "benchmark.hpp"
#include "../external/relaxedPriorityQueues_874280/src/multiqueue/multiqueue.hpp" // Mi Multiqueue

// Adaptador para la Estructura de Datos que sea
template <typename T, typename Compare = std::less<T>>
class HeapAdapter {
private:
    Multiqueue<T, Compare> mq;

    // Usamos una función estática con thread_local.
    // Así, CADA hilo del benchmark tiene su propio caché 'last_top' sin pisarse.
    static std::optional<T>& get_local_cache() {
        static thread_local std::optional<T> local_top = std::nullopt;
        return local_top;
    }

public:
    using value_type = T;

    HeapAdapter(std::size_t n = 8, int c = 2, Compare comp = Compare()) 
        : mq(n, c, comp) {}

    void push(T val) { 
        mq.push(val); 
    }

    void pop() {
        if (get_local_cache()) {
            get_local_cache().reset(); 
        } else {
            mq.try_pop(); 
        }
    }

    T top() {
        if (!get_local_cache()) {
            get_local_cache() = mq.try_pop(); 
        }
        return get_local_cache().value_or(T()); 
    }

    bool empty() const { 
        return mq.empty(); 
    }
};

int main() {
    const int N = 100000;
    const int VISUALIZAR = 20;
    const std::string output = "../results_/results_mq.csv";
    const std::string name = "multiqueue_n32c2";
    const int THREADS = std::thread::hardware_concurrency();

    // Estructura de Datos
    HeapAdapter<int, std::less<int>> heapTest(THREADS*4, 2, std::less<int>());
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}