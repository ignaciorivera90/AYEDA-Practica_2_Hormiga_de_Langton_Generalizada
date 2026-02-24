/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Grado en Ingenieria Informatica
 * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
 * Curso: 2º
 * Practica 2: Hormiga de Langton Generalizada
 *
 * Autor: Ignacio Andres Rivera Barrientos
 * Correo: alu0101675053@ull.edu.es
 * Fecha: 22/02/2026
 *
 * Archivo: main.cc
 * Descripcion: Funcion principal del programa.
 *              Gestiona los argumentos de entrada y lanza la simulacion.
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#include <iostream>
#include "simulator.h"
#include "arg_parser.h"

int main(int argc, char* argv[]) {
  try {
    std::string input = ArgParser::Parse(argc, argv);
    if (input.empty()) return 0;

    Simulator sim(input);
    sim.Run();

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}