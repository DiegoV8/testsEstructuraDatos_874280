#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include "benchmark.hpp"
#include "../external/relaxedPriorityQueues_874280/src/multiqueue/multiqueue.hpp"

// Adaptador para la Estructura de Datos que sea
template <typename T, typename Compare = std::less<T>>
class HeapAdapter {
private:
    Multiqueue<T, Compare> mq;

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

    bool try_pop(T& result) {
        // (Esto pasa si el benchmark llamó a top() pero aún no a pop())
        if (get_local_cache()) {
            result = get_local_cache().value();
            get_local_cache().reset(); // Limpiamos el caché
            return true;
        }
        
        auto opt = mq.try_pop(); 
        if (opt.has_value()) {
            result = opt.value();
            return true; // Extracción exitosa
        }
        
        return false; // La cola está vacía
    }
};

int main() {
    const int N = 5000000;
    const int t = 4; // Numero por el que multiplicar el numero de threads para obtener el numero de colas
    const int VISUALIZAR = 20;
    const std::string output = "../results_/results_new.csv";
    const std::string name = "multiqueue_n32c2";
    const int THREADS = std::thread::hardware_concurrency();
    //const int THREADS = 1;

    // Estructura de Datos
    HeapAdapter<int, std::less<int>> heapTest(THREADS*t, 2, std::less<int>());
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}