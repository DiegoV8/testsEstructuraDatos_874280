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
class HeapAdapterMq {
private:
    Multiqueue<T, Compare> mq;

public:
    using value_type = T;

    HeapAdapterMq(std::size_t n = 8, int c = 2, Compare comp = Compare()) 
        : mq(n, c, comp) {}

    void push(T val) { 
        mq.push(val); 
    }

    std::optional<T> try_pop() {
        return mq.try_pop();
    }

    bool empty() const { 
        return mq.empty(); 
    }
};

int main(int argc, char *argv[]) { // N, t, VISUALIZAR, nombre, THREADS

    if (argc != 6) {
        std::cout << "Numero incorrecto de parametros." << std::endl;
        return 1;
    }

    const int N = atoi(argv[1]);
    const int t = atoi(argv[2]); // Numero por el que multiplicar el numero de threads para obtener el numero de colas
    const int VISUALIZAR = atoi(argv[3]);
    const std::string name = argv[4];
    const int THREADS = atoi(argv[5]);

    const std::string output = "results_/results.csv";

    // Estructura de Datos
    HeapAdapterMq<int, std::less<int>> heapTest(THREADS*t, 2, std::less<int>());
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}