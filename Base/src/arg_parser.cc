/**
  * Universidad de La Laguna
  * Escuela Superior de Ingenieria y Tecnologia
  * Grado en Ingenieria Informatica
  * Asignatura: Algoritmos y Estructuras de Datos Avanzadas
  * Curso: 2º
  * Practica 1:  Hormiga de Langton
  * Autor: Ignacio Andres Rivera Barrientos
  * Correo: alu0101675053@ull.edu.es
  * Fecha: 05/02/2026

  * Archivo arg_parser.cc: Implementacion de la clase ArgParser y funciones utilizadas.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */
#include "arg_parser.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>



/**
 * @brief Checks if a file exists and can be opened.
 * @param filename Path to the file.
 * @return true if the file can be opened, false otherwise.
 *
 * This is used by the argument parser to validate the input file
 * without fully processing it.
 */
bool FileExists(const std::string& filename) {
  std::ifstream file(filename);
  return file.good();   // true si existe y se pudo abrir
}



/**
 * @brief Prints the expected input file format (assignment format).
 *
 * This function is only used when showing help information.
 * It is kept as a static helper because it is only needed in this file.
 */
void PrintFormatINPUT() {
  std::cout << "\n==============================\n";
  std::cout << "    PRACTICA 2 - AYEDA\n";
  std::cout << "  Hormiga de Langton Generalizada\n";
  std::cout << "==============================\n\n";

  std::cout << "Formato del fichero de entrada:\n\n";

  std::cout << "Linea 1:\n";
  std::cout << "  sizeX sizeY numColors\n";
  std::cout << "  - sizeX: numero de columnas\n";
  std::cout << "  - sizeY: numero de filas\n";
  std::cout << "  - numColors: numero total de colores (>= 2)\n\n";

  std::cout << "Linea 2:\n";
  std::cout << "  TIPO x y ORIENT ; TIPO x y ORIENT ; ...\n";
  std::cout << "  - TIPO: regla de la hormiga (ej: DDID, DI, DDII, IDID)\n";
  std::cout << "  - x y: posicion inicial\n";
  std::cout << "  - ORIENT: direccion inicial (^ v < >)\n";
  std::cout << "  - Las hormigas se separan con ';'\n\n";

  std::cout << "Lineas siguientes (opcional):\n";
  std::cout << "  x y color\n";
  std::cout << "  - Define celdas con color distinto de 0 (blanco)\n";
  std::cout << "  - color debe estar en el rango [0, numColors-1]\n\n";

  std::cout << "Ejemplo:\n";
  std::cout << "  10 10 4\n";
  std::cout << "  DDID 5 5 > ; IDID 2 3 ^\n";
  std::cout << "  4 4 1\n";
  std::cout << "  6 6 2\n\n";
}



/**
 * @brief Parses command line arguments and returns the input file path.
 * @param argc Number of arguments.
 * @param argv Array of argument strings.
 * @return Input file path, or empty string if help was requested.
 * @throws std::invalid_argument if number of arguments is incorrect.
 * @throws std::runtime_error if input file does not exist or cannot be opened.
 *
 * Supported usage:
 *  - program input.txt
 *  - program --help / -h
 */
std::string ArgParser::Parse(int argc, char* argv[]) {
  // Help: imprime y no es error
  bool help_requested = false;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
      PrintHelp(argv[0]);
      help_requested = true;
      return "";  // main() puede hacer return 0;
    }
  }

  // Esperamos exactamente 1 argumento de entrada: prog input.txt
  if (argc != 2 && !help_requested) {
    throw std::invalid_argument("Numero de argumentos invalido.");
  }

  const std::string input_file = argv[1];
  if (!FileExists(input_file)) {
    throw std::runtime_error("El fichero de entrada no existe o no se puede abrir: " + input_file);
  }

  return input_file;
}



/**
 * @brief Prints a short usage message.
 * @param progname Program name (argv[0]).
 */
void ArgParser::PrintUsage(const char* progname) {
  std::cout << "Uso: " << progname << " input.txt \n"
            << "Pruebe con --help o -h para mas informacion.\n";
}



/**
 * @brief Prints full help information for the program.
 * @param progname Program name (argv[0]).
 *
 * It includes a brief description and the expected input format.
 */
void ArgParser::PrintHelp(const char* progname) {
  std::cout << "Simulador del comportamiento de la hormiga de Langton\n"
            << "Uso: " << progname << " input.txt\n";
  PrintFormatINPUT();
}
