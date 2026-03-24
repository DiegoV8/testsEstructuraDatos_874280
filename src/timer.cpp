#include "timer.hpp"

void Timer::start() {
    start_node = std::chrono::high_resolution_clock::now();
}

double Timer::stop() {
    auto end_node = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_node - start_node;
    return duration.count();
}