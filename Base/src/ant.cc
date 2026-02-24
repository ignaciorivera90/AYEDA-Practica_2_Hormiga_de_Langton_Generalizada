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
 * Archivo: ant.cc
 * Descripcion: Implementacion de los metodos comunes de la clase Ant,
 *              incluyendo giros, movimiento y representacion del simbolo.
 * Referencias:
 *   - Enunciado oficial de la practica 2.
 *   - Documentacion de C++ (std::vector, std::string, etc.).
 *
 * Historial de revisiones:
 *   22/02/2026 - Creacion inicial de la practica 2.
 */

#include "ant.h"
#include "tape.h"
#include <stdexcept>



/**
 * @brief Returns the character representing the current direction.
 * @return '^', 'v', '<' or '>'.
 */
char Ant::Symbol() const {
  switch (dir_) {
    case Direction::Up: return '^';
    case Direction::Right: return '>';
    case Direction::Down: return 'v';
    case Direction::Left: return '<';
  }
  return '?';
}



/**
 * @brief Rotates the ant 90 degrees to the right.
 */
void Ant::TurnRight() {
  dir_ = static_cast<Direction>((static_cast<int>(dir_) + 1) % 4);
}



/**
 * @brief Rotates the ant 90 degrees to the left.
 */
void Ant::TurnLeft() {
  dir_ = static_cast<Direction>((static_cast<int>(dir_) + 3) % 4);
}



/**
 * @brief Moves the ant one cell forward.
 * @param tape Reference to the world.
 * @throws std::out_of_range if the ant exits the board.
 */
void Ant::MoveForward(const Tape& tape) {
  int nx = x_, ny = y_;
  switch (dir_) {
    case Direction::Up:    ny--; break;
    case Direction::Right: nx++; break;
    case Direction::Down:  ny++; break;
    case Direction::Left:  nx--; break;
  }
  if (!tape.InBounds(nx, ny)) {
    throw std::out_of_range("Ant moved out of bounds");
  }
  x_ = nx;
  y_ = ny;
}