#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include "timer.hpp"

/**
 * @brief Escribe los resultados de benchmark en el archivo csv proporcionado.
 * @tparam structDat Nombre de la estructura de datos probada.
 * @tparam N Numero de datos con los que se ha realizado el test.
 * @tparam t_ins Tiempo de inserción obtenido en el test (Total, no por elemento)
 * @tparam t_ext Tiempo de extracción obtenido en el test (Total, no por elemento)
 * @tparam inversiones Cantidad de elementos mal posicionados.
 * @tparam desp_medio Desplazamiento promedio de los elementos respecto a su posición en la lista ordenada.
 * @tparam desp_var Variación de los elementos respecto a desp_medio.
 * @tparam f_name Nombre del fichero de salida
 */
void print_Results(std::string structDat, int N, double t_ins, double t_ext, int inversiones, double desp_medio, double desp_var, std::string f_name, int nThreads){
    
    std::ifstream check_file(f_name);
    bool escribir_cabecera = false;

    // Si no se puede abrir, es que no existe. 
    // Si se abre, comprobamos si esta vacio
    if (!check_file.is_open() || check_file.peek() == std::ifstream::traits_type::eof()) {
        escribir_cabecera = true;
    }
    check_file.close();
    
    std::ofstream archivo(f_name, std::ios::app);

    if (archivo.is_open()) {
        if (escribir_cabecera) {
            archivo << "nombre_estructura;"
                    << "numero_threads;"
                    << "numero_elementos;"
                    << "tiempo_insercion;"
                    << "tiempo_extraccion;"
                    << "inversiones;" 
                    << "error_medio;"
                    << "desviacion" << std::endl;
        }

        archivo << structDat << ";"
                << nThreads << ";" 
                << N << ";" 
                << t_ins << ";" 
                << t_ext << ";" 
                << inversiones << ";"
                << desp_medio << ";"
                << desp_var << std::endl; // std::endl asegura el salto de línea para la próxima ejecución

        archivo.close(); // Siempre cerrar el flujo al terminar
        std::cout << "Datos guardados en: " << f_name << std::endl;
    }
}

/**
 * @brief Ejecuta pruebas de rendimiento sobre una estructura de datos.
 * @tparam T Tipo de dato contenido (int, float, etc.)
 * @tparam Structure Tipo de la estructura (debe tener push, pop, top, empty)
 * @tparam NUM_ELEMENTOS Número de datos a insertar.
 * @tparam VER_PRIMEROS_N Numero de elementos maximos a mostrar.
 */
template <class Structure>
void run_benchmark(Structure& ds, int NUM_ELEMENTOS, int VER_PRIMEROS_N, std::string structDat, std::string n_fich, int NUM_THREADS) {
    Timer timer;
    std::vector<int> data(NUM_ELEMENTOS);

    // Asigna los valores de 1-NUM_ELEMENTOS
    std::iota(data.begin(), data.end(), 1);

    // Barajamos el orden de la entrada
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    auto worker_insert = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            ds.push(data[i]);
        }
    };

    std::cout << "Iniciando pruebas..." << std::endl;
    std::cout << "Estructura de datos: " << structDat << std::endl;
    std::cout << "Numero de elementos: " << NUM_ELEMENTOS << std::endl;
    std::cout << "Elementos a visualizar: " << VER_PRIMEROS_N << std::endl;
    std::cout << "Fichero de salida: " << n_fich << std::endl;

    // ==========================================
    // 1. TEST DE INSERCIÓN (RENDIMIENTO CONCURRENTE)
    // ==========================================
    std::vector<std::thread> threads;
    int chunk = NUM_ELEMENTOS / NUM_THREADS;

    timer.start();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker_insert, i * chunk, (i == NUM_THREADS - 1) ? NUM_ELEMENTOS : (i + 1) * chunk);
    }
    for (auto& t : threads) t.join();
    double insert_time = timer.stop();

    // ==========================================
    // 2. TEST DE EXTRACCIÓN (RENDIMIENTO CONCURRENTE)
    // ==========================================
    threads.clear();
    
    // Aquí solo sacamos los elementos lo más rápido posible para medir tiempo
    auto worker_extract_time = [&]() {
        while (true) {
            if (ds.empty()) break; 
            
            // Hacemos el top y pop, pero desechamos el valor
            ds.top();
            ds.pop();
        }
    };

    timer.start();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker_extract_time);
    }
    for (auto& t : threads) t.join();
    double extract_time = timer.stop();

    // ==========================================
    // 3. RELLENO DE DATOS (CONCURRENTE)
    // ==========================================
    // Volvemos a meter los datos concurrentemente para la prueba de precisión
    threads.clear();
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker_insert, i * chunk, (i == NUM_THREADS - 1) ? NUM_ELEMENTOS : (i + 1) * chunk);
    }
    for (auto& t : threads) t.join();

    // ==========================================
    // 4. TEST DE PRECISIÓN (EXTRACCIÓN SECUENCIAL)
    // ==========================================
    std::vector<typename Structure::value_type> extracted;
    extracted.reserve(NUM_ELEMENTOS); 

    // Extracción secuencial, sin hilos, asegura que vemos el orden real de la cola
    while (!ds.empty()) {
        auto val = ds.top();
        ds.pop();
        if (val != 0) {
            extracted.push_back(val);
        }
    }

    // ==========================================
    // 5. CÁLCULO DE MÉTRICAS Y PRECISIÓN
    // ==========================================
    int inversions = 0;
    for (size_t i = 0; i < extracted.size() - 1; ++i) {
        if (extracted[i] < extracted[i+1]) {
            inversions++;
        }
    }

    double suma_errores = 0.0;
    int n = (int)extracted.size();
    double error_medio = -1;
    double desviacion = -1;

    if (n > 0) {
        // Error Medio
        for (int i = 0; i < n; ++i) {
            int valor_teorico = NUM_ELEMENTOS - i;
            suma_errores += std::abs((int)extracted[i] - valor_teorico);
        }
        error_medio = suma_errores / n;

        // Desviación Típica
        double suma_cuadrados = 0.0;
        for (int i = 0; i < n; ++i) {
            int valor_teorico = NUM_ELEMENTOS - i;
            double error_i = std::abs((int)extracted[i] - valor_teorico);
            suma_cuadrados += std::pow(error_i - error_medio, 2);
        }
        desviacion = std::sqrt(suma_cuadrados / n);
    }

    // --- SALIDA DE DATOS ---
    std::cout << "\n>>> BENCHMARK REPORT <<<" << std::endl;
    std::cout << "Tiempo Inserción:  " << insert_time << " ms" << std::endl;
    std::cout << "Tiempo Extracción: " << extract_time << " ms" << std::endl;
    std::cout << "Errores de orden (Inversiones): " << inversions << std::endl;
    std::cout << "Error medio de posición: " << error_medio << std::endl;
    std::cout << "Desviación típica: " << desviacion << std::endl;
    std::cout << std::endl;
    std::cout << "Primeros " << VER_PRIMEROS_N << " datos extraídos: ";
    for (int i = 0; i < std::min((int)extracted.size(), VER_PRIMEROS_N); ++i) {
        std::cout << extracted[i] << (i == VER_PRIMEROS_N - 1 ? "" : ", ");
    }
    std::cout << "\n------------------------" << std::endl;

    print_Results(structDat, NUM_ELEMENTOS, insert_time, extract_time, inversions, error_medio, desviacion, n_fich, NUM_THREADS);
}

#endif