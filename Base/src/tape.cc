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
 * Archivo: tape.cc
 * Descripcion: Implementacion de la clase Tape.
 *              Contiene la logica para gestionar colores y limites.
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#include "tape.h"
#include <stdexcept>



/**
 * @brief Constructs a world with given size and number of colors.
 * @param sx Number of columns.
 * @param sy Number of rows.
 * @param num_colors Total number of colors (>=2).
 * @throws std::invalid_argument if values are invalid.
 */
Tape::Tape(int sx, int sy, int num_colors)
    : size_x_(sx), size_y_(sy), num_colors_(num_colors),
      world_(sy, std::vector<uint8_t>(sx, 0)) {
  if (sx <= 0 || sy <= 0) throw std::invalid_argument("Tape size must be > 0");
  if (num_colors < 2) throw std::invalid_argument("num_colors must be >= 2");
}



/**
 * @brief Checks if coordinates are inside the board.
 * @return true if valid position.
 */
bool Tape::InBounds(int x, int y) const {
  return (x >= 0 && x < size_x_ && y >= 0 && y < size_y_);
}



/**
 * @brief Returns the next color in cyclic order.
 * @param c Current color.
 * @return (c + 1) % num_colors.
 */
uint8_t Tape::GetColor(int x, int y) const {
  return world_[y][x];
}



/**
 * @brief Sets the color of a cell in the world.
 * @param x Column index.
 * @param y Row index.
 * @param c New color value.
 * @throws std::out_of_range if the color is outside the valid range [0, num_colors-1].
 */
void Tape::SetColor(int x, int y, uint8_t c) {
  if (c >= static_cast<uint8_t>(num_colors_))
    throw std::out_of_range("Cell color out of range");
  world_[y][x] = c;
}



/**
 * @brief Computes the next color in cyclic order.
 * @param c Current cell color.
 * @return The next color calculated as (c + 1) % num_colors.
 *
 * This function is used to update the color of a cell after
 * an ant visits it, following the generalized Langton's rule.
 */
uint8_t Tape::NextColor(uint8_t c) const {
  return static_cast<uint8_t>((c + 1) % num_colors_);
}