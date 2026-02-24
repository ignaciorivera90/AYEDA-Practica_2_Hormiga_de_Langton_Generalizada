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
 * Archivo: tape.h
 * Descripcion: Declaracion de la clase Tape que representa el mundo
 *              bidimensional de la simulacion.
 *              Gestiona el tamaño, numero de colores y acceso a celdas.
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#pragma once
#include <vector>
#include <cstdint>

class Tape {
 public:
  Tape() = default;
  Tape(int sx, int sy, int num_colors);

  bool InBounds(int x, int y) const;

  uint8_t GetColor(int x, int y) const;
  void SetColor(int x, int y, uint8_t c);

  uint8_t NextColor(uint8_t c) const;

  int size_x() const { return size_x_; }
  int size_y() const { return size_y_; }
  int num_colors() const { return num_colors_; }

 private:
  int size_x_{0};
  int size_y_{0};
  int num_colors_{2};
  std::vector<std::vector<uint8_t>> world_;
};