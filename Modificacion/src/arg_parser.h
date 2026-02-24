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

  * Archivo arg_parser.h: Declaracion de la clase ArgParser.
  *
  * Referencias:
  *      Enlaces de interes

  * Historial de revisiones:
  *      05/02/2026 - Creacion (primera version) del codigo
  */
#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>

class ArgParser {
 public:
  static std::string Parse(int argc, char* argv[]);
  static void PrintUsage(const char* progname);
  static void PrintHelp(const char* progname);

 private:
  ArgParser() = delete;
};

#endif // ARG_PARSER_H
