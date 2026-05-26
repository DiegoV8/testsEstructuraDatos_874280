#include "timer.hpp"

/**
 * @brief Inicia el temporizador.
 */
void Timer::start() {
    start_node = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Para el temporizador, devuelve el tiempo transcurrido desde su inicio.
 * @return double con el tiempo el milisegundos que ha pasado desde el inicio a la parada del temporizador.
 */
double Timer::stop() {
    auto end_node = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end_node - start_node;
    return duration.count();
}