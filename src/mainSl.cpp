#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include "benchmark.hpp"
#include "../external/relaxedPriorityQueues_874280/src/skiplist/skiplist.hpp"

// Adaptador para la Estructura de Datos que sea
template <typename T, typename Compare = std::greater<T>>
class HeapAdapterSl {
private:
    Skiplist<T, Compare> sl;

public:
    using value_type = T;

    HeapAdapterSl(Compare comp = Compare(), int rel = 0) 
        : sl(comp, rel) {}

    void push(T val) { 
        sl.push(val); 
    }

    std::optional<T> try_pop() { 
        return sl.try_pop(); 
    }

    bool empty() const { 
        return sl.empty(); 
    }

    std::size_t size() const {
        return sl.size();
    }
};

int main(int argc, char *argv[]) { // N, VISUALIZAR, nombre, THREADS

    if (argc != 5) {
        std::cout << "Numero incorrecto de parametros." << std::endl;
        return 1;
    }

    const int N = atoi(argv[1]);
    const int VISUALIZAR = atoi(argv[2]);
    const std::string name = argv[3];
    const int THREADS = atoi(argv[4]);

    const std::string output = "results_/results_test.csv";

    // Estructura de Datos
    HeapAdapterSl<int, std::greater<int>> heapTest{std::greater<int>(), 2*THREADS};
    run_benchmark(heapTest, N, VISUALIZAR, name, output, THREADS);

    return 0;
}