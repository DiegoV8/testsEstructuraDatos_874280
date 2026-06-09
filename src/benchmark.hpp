#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <fstream>
#include <random>
#include <numeric>
#include <mutex>
#include <atomic>
#include <omp.h> // Añadida la librería OpenMP (reemplaza a <execution>)
#include "timer.hpp"

/**
 * @brief Escribe los resultados de benchmark en el archivo csv proporcionado.
 * @param structDat Nombre de la estructura de datos probada.
 * @param N Número de datos con los que se ha realizado el test.
 * @param t_ins Tiempo de inserción obtenido en el test (Total, no por elemento).
 * @param t_ext Tiempo de extracción obtenido en el test (Total, no por elemento).
 * @param inversiones Cantidad de elementos mal posicionados.
 * @param desp_medio Desplazamiento promedio de los elementos respecto a su posición en la lista ordenada.
 * @param desp_var Variación de los elementos respecto a desp_medio.
 * @param f_name Nombre del fichero de salida.
 * @param nThreads Número de hilos de concurrencia que ha empleado el test.
 */
void print_Results(std::string structDat, int N, double t_ins, double t_ext, int inversiones, double desp_medio, double desp_var, std::string f_name, int nThreads){
    
    std::ifstream check_file(f_name);
    bool escribir_cabecera = false;

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
                << desp_var << std::endl;

        archivo.close(); 
        std::cout << "Datos guardados en: " << f_name << std::endl;
    }
}

/**
 * @brief Ejecuta pruebas de rendimiento sobre una estructura de datos.
 * @param ds Tipo de la estructura (debe tener push, try_pop, top, pop, empty).
 * @param NUM_ELEMENTOS Número de datos a insertar.
 * @param VER_PRIMEROS_N Número de elementos maximos a mostrar.
 * @param structDat Nombre de la estructura de datos a usar.
 * @param n_fich Nombre del fichero csv de output.
 * @param NUM_THREADS Numero de hilos de concurrencia a emplear.
 */
template <class Structure>
void run_benchmark(Structure& ds, int NUM_ELEMENTOS, int VER_PRIMEROS_N, std::string structDat, std::string n_fich, int NUM_THREADS) {
    Timer timer;
    std::vector<int> data(NUM_ELEMENTOS);

    std::iota(data.begin(), data.end(), 1);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    // Configuramos OpenMP para usar el número exacto de hilos solicitados
    omp_set_num_threads(NUM_THREADS);

    std::cout << "Iniciando pruebas..." << std::endl;
    std::cout << "Estructura de datos: " << structDat << std::endl;
    std::cout << "Numero de elementos: " << NUM_ELEMENTOS << std::endl;
    std::cout << "Elementos a visualizar: " << VER_PRIMEROS_N << std::endl;
    std::cout << "Fichero de salida: " << n_fich << std::endl;
    std::cout << "Hilos configurados (OpenMP): " << NUM_THREADS << std::endl;

    std::cout << "Iniciando inserción concurrente..." << std::endl;
    timer.start();
    
    #pragma omp parallel for
    for (int i = 0; i < NUM_ELEMENTOS; ++i) {
        ds.push(data[i]);
    }
    
    double insert_time = timer.stop();

    std::cout << "Iniciando extracción concurrente..." << std::endl;
    timer.start();
    
    // Todos los hilos entran en esta región y compiten por vaciar la estructura
    #pragma omp parallel
    {
        while (!ds.empty()) {
            auto res = ds.try_pop();
        }
    }

    double extract_time = timer.stop();

    std::cout << "Rellenando estructura para test de precisión..." << std::endl;
    
    #pragma omp parallel for
    for (int i = 0; i < NUM_ELEMENTOS; ++i) {
        ds.push(data[i]);
    }

    std::cout << "Test de Precisión..." << std::endl;
    std::vector<typename Structure::value_type> extracted;
    extracted.reserve(NUM_ELEMENTOS); 

    while (true) {
        auto val = ds.try_pop();
        if (!val) break;

        extracted.push_back(*val);
    }

    std::cout << "Calculando Métricas..." << std::endl;
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
        for (int i = 0; i < n; ++i) {
            int valor_teorico = NUM_ELEMENTOS - i;
            suma_errores += std::abs((int)extracted[i] - valor_teorico);
        }
        error_medio = suma_errores / n;

        double suma_cuadrados = 0.0;
        for (int i = 0; i < n; ++i) {
            int valor_teorico = NUM_ELEMENTOS - i;
            double error_i = std::abs((int)extracted[i] - valor_teorico);
            suma_cuadrados += std::pow(error_i - error_medio, 2);
        }
        desviacion = std::sqrt(suma_cuadrados / n);
    }

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